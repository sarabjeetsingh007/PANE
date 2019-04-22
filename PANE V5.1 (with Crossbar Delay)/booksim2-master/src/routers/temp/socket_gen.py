before = ["ADDR ["]
before1 = ["]["]
before2 = ["] = "]
first = ["\"../../socket_r"]
second = ["_c"]
third = ["_i"]
line = []
out = open("SockList", "w")
for i in range(16):
    for j in range(4):
        for k in range(5):
            line = line + before + [str(i)] + before1 + [str(j)] + before1 + [str(k)] + before2 + first + [str(i)] + second + [str(j)] + third + [str(k)] + ["\";\n"]

new_line = "".join(line)
out.writelines(line)
out.close()
            
