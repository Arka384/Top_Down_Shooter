fp = open('map1.txt','r')
content = fp.read()

content = content.replace(","," ")
print(content)

fp = open("map_mod_1.txt", "w")
fp.write(content)

fp.close()