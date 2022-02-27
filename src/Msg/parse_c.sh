#!/bin/bash

function_generate_config() {
    echo $(basename ${msg_header_macro}) | sed 's/.msg//g' >> ${msgconf}
}

function_msg_var_to_c_style() {
    var_name=()
    var_type=()
    var_subscript=()
    while IFS= read -r line;
    do
        prefix=```echo ${line} | awk '{print $1}'```
        postfix=```echo ${line} | awk '{print $2}'```
        var_name[${#var_name[@]}]=${postfix}
        var_type[${#var_type[@]}]=```echo ${prefix} | awk '{print $1}' | sed 's/[]|[0-9]//g'```
        var_subscript[${#var_subscript[@]}]=```echo ${prefix} | sed 's/[]|[[:alpha:][:blank:]]//g' ```
    done < ${msg_file}
}

function_msg_header() {
    msg_basename=```basename ${msg_file} | sed 's/.msg//g'```
    msg_type=```echo "$msg_basename" | awk '{print tolower($0)}'```;
    msg_header_macro=```echo "$msg_basename" | awk '{print toupper($0)}'```;
    # function_generate_config
}

function_generate_header() {
    rm -rf ${inc}/${msg_basename}.h

    cp ${inc}/template.h ${inc}/${msg_basename}.h

    # header section
    sed -i 's/TEMPLETE/'"$msg_header_macro"'/g' ${inc}/${msg_basename}.h

    # struct section
    struct_section="struct _";
    struct_section+=${msg_type}"{"
    struct_section+='\n'

    for var_idx in $(seq 0 $((${#var_type[@]}-1)));
    do
        struct_section+='\t'
        struct_section+=${var_type[${var_idx}]}
        struct_section+=' '
        struct_section+=${var_name[${var_idx}]}

        if [[ ${#var_subscript[${var_idx}]} != 0 ]]
        then
            struct_section+='['${var_subscript[${var_idx}]}']'
        fi
        struct_section+=';';
        struct_section+='\n'
    done

    struct_section+="};\n\n"

    struct_section+="void ${msg_basename}_message_pack(char*, struct _${msg_type}, char*);\n"
    struct_section+="void ${msg_basename}_message_unpack(char*, struct _${msg_type}*);\n"
    
    sed -i 's/struct _templete;/'"$struct_section"'/g' ${inc}/${msg_basename}.h

}

function_generate_int() {
    add_topic_name_section+='\t'"${var_name[${var_idx}]}_json = cJSON_CreateNumber(${number});\n"
    add_topic_name_section+='\t'"cJSON_AddItemToObject(new_msg, \"${var_name[${var_idx}]}\", ${var_name[${var_idx}]}_json);\n"
}

function_generate_string() {
    add_topic_name_section+='\t'"${var_name[${var_idx}]}_json = cJSON_CreateString(${string});\n"
    add_topic_name_section+='\t'"cJSON_AddItemToObject(new_msg, \"${var_name[${var_idx}]}\", ${var_name[${var_idx}]}_json);\n"
}

function_generate_source() {
    rm -rf ${src}/${msg_basename}.c

    cp ${src}/template.c ${src}/${msg_basename}.c

    sed -i 's/templete.h/'${msg_basename}.h'/g' ${src}/${msg_basename}.c

    sed -i 's/_message/'${msg_basename}'_message/g' ${src}/${msg_basename}.c

    ### pack ###
    
    # Replace type of argument
    sed -i 's/_templete/''_'"${msg_type}"'/g' ${src}/${msg_basename}.c

    # CREATE_TOPIC_NAME_FILED_SCECTION
    create_topic_name_field_section=
    #create_topic_name_field_section='\t'"topic_name = "
    #create_topic_name_field_section+="cJSON_CreateString("\"${msg_basename}"\");\n"
    #create_topic_name_field_section+='\t'"cJSON_AddItemToObject(new_msg, \"topic_name\", topic_name);\n"

    sed -i 's/CREATE_TOPIC_NAME_FILED_SCECTION/'"$create_topic_name_field_section"'/g' ${src}/${msg_basename}.c
    
    # CREATE_TYPE_SCECTION
    create_type_section='\t'"type_name = "
    create_type_section+="cJSON_CreateString("\"${msg_header_macro}"\");\n"
    create_type_section+='\t'"cJSON_AddItemToObject(new_msg, \"type_name\", type_name);\n"

    sed -i 's/CREATE_TYPE_SCECTION/'"$create_type_section"'/g' ${src}/${msg_basename}.c
    
    # DECLARE_SCECTION
    declare_section=
    for var_idx in $(seq 0 $((${#var_type[@]}-1)));
    do
        declare_section+='\t'
        declare_section+="cJSON "'\*'
        declare_section+=${var_name[${var_idx}]}_json
        declare_section+=" = NULL"
        declare_section+=";"
        declare_section+='\n'
    done

    sed -i 's/DECLARE_SCECTION/'"$declare_section"'/g' ${src}/${msg_basename}.c

    # ADD_TOPIC_NAME_SECTION
    add_topic_name_section=
    for var_idx in $(seq 0 $((${#var_type[@]}-1)));
    do
        # array
        if [[ ${#var_subscript[${var_idx}]} != 0 ]]
        then
            # string
            if [[ ${var_type[${var_idx}]} == "char" ]]
            then
                string="type.${var_name[${var_idx}]}"
                function_generate_string
            else
                # Not string
                add_topic_name_section+='\n'
                add_topic_name_section+='\t'"cJSON *""${var_name[${var_idx}]}_ary = cJSON_CreateArray();\n"
                add_topic_name_section+='\t'"cJSON_AddItemToObject(new_msg, "\"${var_name[${var_idx}]}"\", ${var_name[${var_idx}]}_ary);\n"

                array_count=0
                array_count=${var_subscript[${var_idx}]}

                add_topic_name_section+='\t'"for (int idx = 0; idx < "${array_count}"; idx++) {\n"
                add_topic_name_section+="\t\t""${var_name[${var_idx}]}_json = cJSON_CreateNumber(type.${var_name[${var_idx}]}[idx]);"'\n'

                add_topic_name_section+="\t\t""cJSON_AddItemToArray(${var_name[${var_idx}]}_ary, ${var_name[${var_idx}]}_json);\n"
                add_topic_name_section+='\t'"}"'\n'
            fi
        else
            # Not array
            number="type.${var_name[${var_idx}]}"
            function_generate_int
        fi
    done

    sed -i 's/ADD_TOPIC_NAME_SECTION/'"$add_topic_name_section"'/g' ${src}/${msg_basename}.c

    ### unpack ###

    # UNPACK_PACKAGE
    unpack_package=
    unpack_package+='\t'"int idx = 0;\n\n"
    for var_idx in $(seq 0 $((${#var_type[@]}-1)));
    do
        if [[ ${#var_subscript[${var_idx}]} != 0 ]]
        then
            # array
            # string
            if [[ ${var_type[${var_idx}]} == "char" ]]
            then
                unpack_package+='\t'"${var_name[${var_idx}]}_json = cJSON_GetObjectItemCaseSensitive(new_msg, "\"${var_name[${var_idx}]}"\");"
                unpack_package+='\n'
                unpack_package+='\t'"strcpy(ret->${var_name[${var_idx}]}, ${var_name[${var_idx}]}_json->valuestring);\n"
            else
                unpack_package+='\t'"cJSON *${var_name[${var_idx}]}_json_ary = cJSON_GetObjectItemCaseSensitive(new_msg, "\"${var_name[${var_idx}]}"\");"
                unpack_package+='\n'
                unpack_package+='\t'"idx = 0;\n"
                unpack_package+='\t'"cJSON_ArrayForEach(${var_name[${var_idx}]}_json, ${var_name[${var_idx}]}_json_ary) {\n"
                unpack_package+="\t\t""ret->${var_name[${var_idx}]}[idx] = ${var_name[${var_idx}]}_json->valuedouble;"'\n'
                unpack_package+="\t\t""idx++;\n"
                unpack_package+='\t'"}\n\n"
            fi
        else
            # Not array
            unpack_package+='\t'"${var_name[${var_idx}]}_json = "
            unpack_package+="cJSON_GetObjectItemCaseSensitive(new_msg, "\"${var_name[${var_idx}]}"\");\n"
            
            unpack_package+='\t'"if(!cJSON_IsString(${var_name[${var_idx}]}_json)) {\n"
            unpack_package+="\t\t""ret->${var_name[${var_idx}]} = ${var_name[${var_idx}]}_json->valuedouble;\n"
            #unpack_package+="\t} else {\n"
            #unpack_package+="\t\t""strcpy(ret->${var_name[${var_idx}]}, ${var_name[${var_idx}]}_json->valuestring);\n"
            unpack_package+="\t}\n"
        fi
    done

    # cJSON_ArrayForEach

    sed -i 's/UNPACK_PACKAGE/'"${unpack_package}"'/g' ${src}/${msg_basename}.c
}

function_move_source() {
    mv ${inc}/${msg_basename}.h ${topdir}/Core/Message/inc
    mv ${src}/${msg_basename}.c ${topdir}/Core/Message/src
}

topdir=$(pwd)
curdir=$(pwd)/Msg
inc=${curdir}/inc
src=${curdir}/src
msgconf=${curdir}/msg.conf

declare -A var_name
declare -A var_type
declare -A var_symbol
declare -A var_subscript

msg_basename=
msg_type=
msg_header_macro=

msg_path=($(ls ${curdir}/msg/*))

rm -rf ${msgconf}
for msg_file in "${msg_path[@]}";
do
    function_msg_var_to_c_style
    function_msg_header
    function_generate_header
    function_generate_source
    function_move_source
done
