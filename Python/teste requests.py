import json, requests, base64, csv

url = 'https://artimar.orbiwise.com/rest/nodes/0004A30B001A674B/payloads/ul'

## Conecta no API da orbiwise, ignorando a verificacao HTTPS
from requests.auth import HTTPBasicAuth
r = requests.get(url, auth=HTTPBasicAuth('maua_ceun', 'Maua2016'), verify = False)

## Pega o JSON e o ordena pela data recebida
json_string = r.text
parsed_json = json.loads(json_string)
jsonSorted = sorted(parsed_json, key=lambda k: k['timestamp'])

## Decodifica os dados de base64 para HEX
for l in range(0,len(jsonSorted)):
    jsonSorted[l]["dataFrame"] = base64.b64decode(jsonSorted[l]["dataFrame"])
    jsonSorted[l]["dataFrame"] = base64.b16encode(jsonSorted[l]["dataFrame"])

## Grava como CSV
outputFile = open('testeCSV.csv', 'w')
outputWriter = csv.writer(outputFile)
outputWriter.writerow(['Dados HEX', 'Data', 'Port'])
for l in range(0,len(jsonSorted)):
    outputWriter.writerow([jsonSorted[l]["dataFrame"], jsonSorted[l]["timestamp"], jsonSorted[l]["port"]])
outputFile.close()
