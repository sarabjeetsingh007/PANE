maxH=4
maxV=4
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
line = []
outf = open("Network_4X4_Mesh_ned", "w")
for H in range(maxH):
    for V in range(maxV):
	if((H-1)>=0):
		line = line + router + [str(V*maxH + H)]+ out + l + ra + router + [str(V*maxH + (H-1))] + inn + r + ter
		line = line + router + [str(V*maxH + H)]+ acki + l + la + router + [str(V*maxH + (H-1))] + acko + r + ter
	if((V-1)>=0):
		line = line + router + [str(V*maxH + H)]+ out + u + ra + router + [str((V-1)*maxH + H)] + inn + d + ter
		line = line + router + [str(V*maxH + H)]+ acki + u + la + router + [str((V-1)*maxH + H)] + acko + d + ter
	if((H+1)<maxH):
		line = line + router + [str(V*maxH + H)]+ out + r + ra + router + [str(V*maxH + (H+1))] + inn + l + ter
		line = line + router + [str(V*maxH + H)]+ acki + r + la + router + [str(V*maxH + (H+1))] + acko + l + ter
	if((V+1)<maxV):
		line = line + router + [str(V*maxH + H)]+ out + d + ra + router + [str((V+1)*maxH + H)] + inn + u + ter
		line = line + router + [str(V*maxH + H)]+ acki + d + la + router + [str((V+1)*maxH + H)] + acko + u + ter

new_line = "".join(line)
outf.writelines(line)
outf.close()
