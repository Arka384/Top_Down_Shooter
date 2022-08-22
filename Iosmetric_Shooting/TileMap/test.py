fp = open('test_map.txt','r')
content = fp.read()

content = content.replace(","," ")
print(content)

fp = open("map2.txt", "w")
fp.write(content)

fp.close()