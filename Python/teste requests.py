import json, requests, base64, csv

url = 'https://artimar.orbiwise.com/rest/nodes/0004A30B001A674B/payloads/ul/latest'

from requests.auth import HTTPBasicAuth
r = requests.get(url, auth=HTTPBasicAuth('maua_ceun', 'Maua2016'), verify = False)

json_string = r.text
parsed_json = json.loads(json_string)

dataFrame = parsed_json['dataFrame']
dataFrame = base64.b64decode(dataFrame)
dataFrame = base64.b16encode(dataFrame)

port = parsed_json['port']
timestamp = parsed_json['timestamp']
fcnt = parsed_json['fcnt']

outputFile = open('testeCSV.csv', 'w')
outputWriter = csv.writer(outputFile)
outputWriter.writerow(['Pressao', 'Data', 'Port', 'Fcnt'])
outputWriter.writerow([dataFrame, timestamp, port, fcnt])
outputFile.close()
