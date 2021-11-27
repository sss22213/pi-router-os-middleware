#!/uar/bin/lua

require('uci')
uci_cmd = uci.cursor()

local wireless

function get_radio_list ()
	radio_list = {}
	uci_cmd:foreach("wireless", "wifi-device", function(s)
		for key, value in pairs(s) do
			print(key, value)
			if key == '.name' then
				table.insert(radio_list, tostring(value))
			end
		end
	end)
	return radio_list
end

function get_radio_info (radio_name)
	radio_info = {}
	uci_cmd:foreach("wireless", "wifi-device", function(s)
		if s[".name"] == radio_name then
			table.insert(radio_info, s)
		end
	end)
	return radio_info
end

function get_wireless_info (radio_name)
	wirless_info = {}
        uci_cmd:foreach("wireless", "wifi-iface", function(s)
		if s["device"] == radio_name then
			table.insert(wirless_info, s)
		end
        end)
	return wirless_info
end


