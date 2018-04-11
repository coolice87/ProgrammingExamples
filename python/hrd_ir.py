#coding=utf-8

g_array = []
rf_array = []
r_array = []

x_array = []
y_array = []
z_array = []
xyz_array = []
fileOpen = open('./heart_rate./Sensor_1478501390.csv','r')
curSaveFile = open('./heart_rate./Sensor_ir4.csv','w')
count = 0
for line in fileOpen:

    count += 1
    if count < 3 :
       continue

    tmStr =  line.split(',')
    #print tmStr
    r1_str = tmStr[3] + tmStr[2] + tmStr[1] + tmStr[0]
    r2_str = tmStr[7] + tmStr[6] + tmStr[5] + tmStr[4]
    r3_str = tmStr[11] + tmStr[10] + tmStr[9] + tmStr[8]
    r4_str = tmStr[15] + tmStr[14] + tmStr[13] + tmStr[12]
    r5_str = tmStr[19] + tmStr[18] + tmStr[17] + tmStr[16]



    r1 = int(r1_str, 16)
    if r1 > 2147483647:
        r1 = r1 - 4294967295 + 1

    r2 = int(r2_str, 16)
    if r2 > 2147483647:
        r2 = r2 - 4294967295 + 1

    r3 = int(r3_str, 16)
    if r3 > 2147483647:
        r3 = r3 - 4294967295 + 1
		
    r4 = int(r4_str, 16)
    if r4 > 2147483647:
        r4 = r4 - 4294967295 + 1
		
    r5 = int(r5_str, 16)
    if r5 > 2147483647:
        r5 = r5 - 4294967295 + 1
	
    #print g,rf,r
    curSaveFile.writelines(str(r1) + '\n')
    curSaveFile.writelines(str(r2) + '\n')
    curSaveFile.writelines(str(r3) + '\n')
    curSaveFile.writelines(str(r4) + '\n')
    curSaveFile.writelines(str(r5) + '\n')
    
    '''
    x = int(x_str, 16) >> 6
    y = int(y_str, 16) >> 6
    z = int(z_str, 16) >> 6
    g_array.append(g)
    rf_array.append(rf)

    r_array.append(r)
    if x > 512:
        x = x - 1024 +1
    if y > 512:
        y = y - 1024 +1
    if z > 512:
        z = z - 1024 +1
    x = x
    y = y
    z = z

    xyz_array.append(x*x + y*y+ z*z)
    #print x,y,z
    x_array.append(x)
    y_array.append(y)
    z_array.append(z)
    '''