import json, requests, base64, csv

url = 'https://artimar.orbiwise.com/rest/nodes/0004A30B001A674B/payloads/ul'

## Conecta no API da orbiwise, ignorando a verificacao HTTPS
from requests.auth import HTTPBasicAuth
r = requests.get(url, auth=HTTPBasicAuth('maua_ceun', 'Maua2016'))

## Pega o JSON e o ordena pela data recebida
json_string = r.text
parsed_json = json.loads(json_string)
jsonSorted = sorted(parsed_json, key=lambda k: k['timestamp'])

## Decodifica os dados
for l in range(0,len(jsonSorted)):
    #Passa de base64 para HEX
    jsonSorted[l]["dataFrame"] = base64.b64decode(jsonSorted[l]["dataFrame"])
    jsonSorted[l]["dataFrame"] = base64.b16encode(jsonSorted[l]["dataFrame"])

    #Separa os dados e passa para decimal
    jsonSorted[l]["temp"] = jsonSorted[l]["dataFrame"][0:4]
    jsonSorted[l]["temp"] = int(jsonSorted[l]["temp"], 16)
    jsonSorted[l]["temp"] = jsonSorted[l]["temp"] / 10.0
    
    jsonSorted[l]["umid"] = jsonSorted[l]["dataFrame"][4:8]
    jsonSorted[l]["umid"] = int(jsonSorted[l]["umid"], 16)
    jsonSorted[l]["umid"] = jsonSorted[l]["umid"] / 10.0
    
    jsonSorted[l]["pres"] = jsonSorted[l]["dataFrame"][8:12]
    jsonSorted[l]["pres"] = int(jsonSorted[l]["pres"], 16)

## Grava como CSV
outputFile = open('testeCSV.csv', 'w')
outputWriter = csv.writer(outputFile)
outputWriter.writerow(['Temperatura', 'Umidade', 'Pressao', 'Data', 'Dados HEX'])
for l in range(0,len(jsonSorted)):
    outputWriter.writerow([jsonSorted[l]["temp"],jsonSorted[l]["umid"], jsonSorted[l]["pres"],
                           jsonSorted[l]["timestamp"], jsonSorted[l]["dataFrame"]])
outputFile.close()
