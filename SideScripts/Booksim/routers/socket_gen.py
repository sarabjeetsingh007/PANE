numRouters = 64
before = ["ADDR ["]
before1 = ["]["]
before2 = ["] = "]
first = ["\"../../socket_r"]
second = ["_c"]
third = ["_i"]
mytab = ["\t"]
line = []

for i in range(numRouters):
    for j in range(4):
        for k in range(5):
            line = line + mytab + before + [str(i)] + before1 + [str(j)] + before1 + [str(k)] + before2 + first + [str(i)] + second + [str(j)] + third + [str(k)] + ["\";\n"]

new_line = "".join(line)







inFile = open("../../../booksim2-master/src/routers/socket_lib.cpp", "r")
infileRead = inFile.read()

tempLineList = infileRead.split("void assignsocklist()")

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



header += "void assignsocklist()\n" + "{\n\n"

carryBody = "\n\n}\n" + carryBody


out = open("../../../booksim2-master/src/routers/socket_lib.cpp", "w")
out.writelines([header] + line + [carryBody])
out.close()
            
