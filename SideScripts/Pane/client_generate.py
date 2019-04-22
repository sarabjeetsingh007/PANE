import sys
import array




# Input data will in the format of: filename.py number_of_clock_domains 'assigned_routers for clock domain 1' 'assigned_routers for clock domain 2' .................. clock_domain_1_client_index_0 clock_domain_1_client_index_1 ...............clock_domain_lastOne_client_index_4


preTab = "\t"
dataList = sys.argv;


noOfClockDomains = int(dataList[1]);

k = 2

assignedRouters = []

for i in range(noOfClockDomains):
	assignedRouters.append(dataList[k].split(','))
	k += 1


clockDomainClients = []
for i in range(noOfClockDomains):
	clockDomainClients.append([])
	for j in range(4):
		clockDomainClients[i].append(dataList[k])
		k += 1;





conditionalStatements = []
conditionalStatementOuter = ""
k = noOfClockDomains + 1;
for i in range(noOfClockDomains):
	conditionalStatementInner = ""
	
	clientSettingIndex = ""

	for j in range(len(assignedRouters[i])) :
		if (j > 0):
			conditionalStatementInner += " || "

		conditionalStatementInner += "(this->getParentModule()->getIndex() == " + assignedRouters[i][j] + ")"



	# conditionalStatements.append(temp)
	

	if(i == 0):
		conditionalStatementOuter = preTab + "if(" + conditionalStatementInner + ") {\n\n"

	elif(0 < i < (noOfClockDomains-1)) :
		conditionalStatementOuter += preTab + "else if(" + conditionalStatementInner + ") {\n\n"
	
	elif((i == (noOfClockDomains-1)) and i>0):
		conditionalStatementOuter += preTab + "else {\n\n"







	for l in range(4) :
		if (l == 0) :
			clientSettingIndex = preTab + "\tif(this->getIndex()==0) {\n"

		else :
			clientSettingIndex += preTab + "\telse if(this->getIndex()==" + str(l) + ") {\n"
		

		clientSettingIndex += preTab + '\t\ttime_slot = ' + clockDomainClients[i][l] + ';\n'
		clientSettingIndex += preTab + '\t\t//	"EV<<Client ' + str(l) + ' time_slot = " << time_slot << " s\\n";\n'
		clientSettingIndex += preTab + "\t}\n"




	conditionalStatementOuter +=  clientSettingIndex
	conditionalStatementOuter += "\n\n\n" +  preTab + "}\n\n"


	# print conditionalStatement;





inFile = open("../../PANE/client.cc", "r")
infileRead = inFile.read()

tempLineList = infileRead.split("void mod::setupclockdomain()")

header = tempLineList[0]
carryBody = tempLineList[1]


findFxnStartIndex = 0
for item in carryBody:
  findFxnStartIndex += 1
  if (item == "{"):
    break

carryBody = carryBody[findFxnStartIndex:len(carryBody)]



isFound = 1
bodyIndex = 0
for item in carryBody:
  bodyIndex += 1
  if (item == "{"):
    isFound += 1
  elif (item == "}"):
    isFound -= 1
  
  if (isFound == 0):
    carryBody = carryBody[bodyIndex:len(carryBody)]
    break

inFile.close()



header += "void mod::setupclockdomain()\n" + "{\n\n"

carryBody = "\n\n}\n" + carryBody



out = open("../../PANE/client.cc", "w")
out.writelines([header] + [conditionalStatementOuter] + [carryBody])
out.close()
            
