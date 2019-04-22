maxH=8
maxV=8
numRouters = maxH * maxV
router = ["router["]
ra = ["] --> "]
la = ["] <-- "]
ter = ["];\n"]
r = ["r"]
l = ["l"]
u = ["u"]
d = ["d"]
out = ["].out["]
inn = ["].in["]
acko = ["].Ack_out["]
acki = ["].Ack_in["]
mytab = ["\t\t"]
line = []

for H in range(maxH):
    for V in range(maxV):
	if((H-1)>=0):
		line = line + mytab + router + [str(V*maxH + H)]+ out + l + ra + router + [str(V*maxH + (H-1))] + inn + r + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + l + la + router + [str(V*maxH + (H-1))] + acko + r + ter
	if(H==0):
		line = line + mytab + router + [str(V*maxH + H)]+ out + l + ra + router + [str(V*maxH + (H-1) + maxH)] + inn + r + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + l + la + router + [str(V*maxH + (H-1) + maxH)] + acko + r + ter
	if((V-1)>=0):
		line = line + mytab + router + [str(V*maxH + H)]+ out + u + ra + router + [str((V-1)*maxH + H)] + inn + d + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + u + la + router + [str((V-1)*maxH + H)] + acko + d + ter
	if(V==0):
		line = line + mytab + router + [str(V*maxH + H)]+ out + u + ra + router + [str((V-1 + maxV)*maxH + H)] + inn + d + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + u + la + router + [str((V-1 + maxV)*maxH + H)] + acko + d + ter
	if((H+1)<maxH):
		line = line + mytab + router + [str(V*maxH + H)]+ out + r + ra + router + [str(V*maxH + (H+1))] + inn + l + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + r + la + router + [str(V*maxH + (H+1))] + acko + l + ter
	if(H==(maxH-1)):
		line = line + mytab + router + [str(V*maxH + H)]+ out + r + ra + router + [str(V*maxH + (H+1) - maxH)] + inn + l + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + r + la + router + [str(V*maxH + (H+1) - maxH)] + acko + l + ter
	if((V+1)<maxV):
		line = line + mytab + router + [str(V*maxH + H)]+ out + d + ra + router + [str((V+1)*maxH + H)] + inn + u + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + d + la + router + [str((V+1)*maxH + H)] + acko + u + ter
	if(V==(maxV-1)):
		line = line + mytab + router + [str(V*maxH + H)]+ out + d + ra + router + [str((V+1 - maxV)*maxH + H)] + inn + u + ter
		line = line + mytab + router + [str(V*maxH + H)]+ acki + d + la + router + [str((V+1 - maxV)*maxH + H)] + acko + u + ter

new_line = "".join(line)





inFile = open("../../../PANE/network.ned", "r")
infileRead = inFile.read()

tempLineList = infileRead.split("connections:")

header = tempLineList[0]
carryBody = tempLineList[1].split("//Source-Router Communication")[1]

header += "connections:\n"

header += "\t\t//Inter-Router Communication !!Go to network_ned_connections_mesh.py\n\n"


carryBody = "\n\n\t\t//Source-Router Communication" + carryBody
inFile.close()



outf = open("../../../PANE/network.ned", "w")
outf.writelines([header] + line + [carryBody])
outf.close()
