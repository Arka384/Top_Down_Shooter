fp = open('test_3.txt','r')
content = fp.read()

content = content.replace(","," ")

fp = open("map3_3.txt", "w")
fp.write(content)

fp.close()