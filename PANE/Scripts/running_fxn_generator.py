import sys
import time
import os


injectionRate = []
packetSize = []
bufferOrganization_VCs = []
bufferOrganization_bufferSize = []
routingFunctionData = ''
trafficPatternData = '6'

trafficPatternList = ['neighbor', 'uniform', 'tornado', 'shuffle', 'transpose', 'bitcomp', 'bitrev']
routingFunctionList = ['dor', 'xy-yx', 'adaptive xy-yx', 'romm', 'min-adapt', 'planar adapt']



# routingFunction = ''
# trafficPattern = ''


def samplingFxn(start, end, samplingRate, sampledList) :
	if start <= end:
		sampledList.append(start)
		start += samplingRate
		return samplingFxn(start, end, samplingRate, sampledList)

	else :
		return sampledList


def checkboxDataCompile(mList, mString):
	mFinalList = []
	mReceivedList = mString.split(',')
	for i in mReceivedList:
		mFinalList.append(mList[int(i)])

	return mFinalList




line = []
out = open("sweep_run.sh", "w")

line += "cd ../\n\n"
line += "export PATH=$PATH:/home/sarab/Documents/Simulators/omnetpp-5.1/bin\n\n"
# line += "make\n"
# line += "make sock\n"
# line += "gnome-terminal -x sh -c \"(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump/dump_onstart; )\"\n"
# line += "./PANE -u Cmdenv -f omnetpp.ini\n\n"







sampledObjectArray = []
tempSampleCounter = 0
# Populating the sampled object array

if routingFunctionData != '':
	sampledObjectArray.append(tempSampleCounter)
	sampledObjectArray[tempSampleCounter] = {}
	sampledObjectArray[tempSampleCounter]['sampled_data'] = checkboxDataCompile(routingFunctionList, routingFunctionData)
	sampledObjectArray[tempSampleCounter]['command'] = 'routing_function'
	tempSampleCounter += 1

if trafficPatternData != '':
	sampledObjectArray.append(tempSampleCounter)
	sampledObjectArray[tempSampleCounter] = {}
	sampledObjectArray[tempSampleCounter]['sampled_data'] = checkboxDataCompile(trafficPatternList, trafficPatternData)
	sampledObjectArray[tempSampleCounter]['command'] = 'traffic'
	tempSampleCounter += 1


if injectionRate != []:
	sampledObjectArray.append(tempSampleCounter)
	sampledObjectArray[tempSampleCounter] = {}
	sampledObjectArray[tempSampleCounter]['sampled_data'] = samplingFxn(injectionRate[0], injectionRate[1], injectionRate[2], [])
	sampledObjectArray[tempSampleCounter]['command'] = 'injection_rate'
	tempSampleCounter += 1


if packetSize != []:
	sampledObjectArray.append(tempSampleCounter)
	sampledObjectArray[tempSampleCounter] = {}
	sampledObjectArray[tempSampleCounter]['sampled_data'] = samplingFxn(packetSize[0], packetSize[1], packetSize[2], [])
	sampledObjectArray[tempSampleCounter]['command'] = 'packet_size'
	tempSampleCounter += 1

if bufferOrganization_VCs != []:
	sampledObjectArray.append(tempSampleCounter)
	sampledObjectArray[tempSampleCounter] = {}
	sampledObjectArray[tempSampleCounter]['sampled_data'] = samplingFxn(bufferOrganization_VCs[0], bufferOrganization_VCs[1], bufferOrganization_VCs[2], [])
	sampledObjectArray[tempSampleCounter]['command'] = 'num_vcs'
	tempSampleCounter += 1


if bufferOrganization_bufferSize != []:
	sampledObjectArray.append(tempSampleCounter)
	sampledObjectArray[tempSampleCounter] = {}
	sampledObjectArray[tempSampleCounter]['sampled_data'] = samplingFxn(bufferOrganization_bufferSize[0], bufferOrganization_bufferSize[1], bufferOrganization_bufferSize[2], [])
	sampledObjectArray[tempSampleCounter]['command'] = 'vc_buf_size'
	tempSampleCounter += 1



# print sampledObjectArray   //////////////////  Shifted to loop

# if routingFunction != "" :
# 	line += "sed -i \"/routing_function = / c routing_function = " + routingFunction + "\" ../booksim2-master/src/examples/bitrev\n"

# if trafficPattern != "" :
# 	line += "sed -i \"/traffic = / c traffic = " + trafficPattern + "\" ../booksim2-master/src/examples/bitrev\n\n"




commandLine = ""
print "*****************************   Compiling...  *****************************"

def sampleCombination(dumpString, loopCounter) :	
	start_time = time.time()
	if (loopCounter < len(sampledObjectArray)):
		for i in  sampledObjectArray[loopCounter]['sampled_data']:
			global commandLine
			commandLine += "sed -i \"/" + sampledObjectArray[loopCounter]['command'] + " = / c " + sampledObjectArray[loopCounter]['command'] + " = " + str(i) + ";\" ../booksim2-master/src/examples/bitrev\n"
			temp = "_" + sampledObjectArray[loopCounter]['command'] + ":" + str(i)
			sampleCombination(dumpString + temp, loopCounter + 1)
			# dumpString = "dump"
	else:
		commandLine += "make\n"
		commandLine += "make sock\n"
		commandLine += "gnome-terminal -x sh -c \"(sleep 1; cd ../booksim2-master/src/;   ./run.sh > dump/" + dumpString + "; )\"\n"
		commandLine += "./PANE -u Cmdenv -f omnetpp.ini\n\n"


	elapsed_time = time.time() - start_time
	if (elapsed_time > 1):
		sys.stdout.write("#")
    	sys.stdout.flush()



sampleCombination('dump', 0)

print "\nDone !!!!!!!!!!!!"

line += commandLine



# Restoring bitrev file to defaut values
# line += "sed -i \"/routing_function = / c routing_function = dor\" ../booksim2-master/src/examples/bitrev\n"
# line += "sed -i \"/injection_rate = / c injection_rate = 0.5\" ../booksim2-master/src/examples/bitrev\n"
# line += "sed -i \"/packet_size = / c packet_size = 1\" ../booksim2-master/src/examples/bitrev\n"



out.writelines(line)
out.close()


# Running Sweep run file after compiling the it
os.system("gnome-terminal -x sh -c \"( chmod +x sweep_run.sh;)\"")
os.system("gnome-terminal -x sh -c \"(./sweep_run.sh;)\"")
