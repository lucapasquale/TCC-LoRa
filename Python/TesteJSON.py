import json, base64, urllib.request

top_level_url = 'https://artimar.orbiwise.com/rest/nodes/0004A30B001A674B/payloads/ul/latest'

username = 'maua_ceun'
password = 'Maua2016'

p = urllib.request.HTTPPasswordMgrWithDefaultRealm()
p.add_password(None, top_level_url, username, password)

auth_handler = urllib.request.HTTPBasicAuthHandler(p)

opener = urllib.request.build_opener(auth_handler)

urllib.request.install_opener(opener)

try:
    result = opener.open(top_level_url)
    messages = result.read()
    print (messages)
except IOError as e:
    print (e)
    

#json_string = '{"dataFrame":"CTA=","port":30,"timestamp":"2016-05-19 17:16:24.596","fcnt":806,"rssi":-105,"snr":7,"sf_used":"10","id":188404,"decrypted":true}'
#parsed_json = json.loads(json_string)

#dataFrame = parsed_json['dataFrame']
#dataBit = base64.b64decode(dataFrame)
#dataHex = base64.b16encode(dataBit)


#print(dataHex)




