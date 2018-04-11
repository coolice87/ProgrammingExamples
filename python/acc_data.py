#coding=utf-8

curSaveFile =  open('./test4.csv','w')
#curSaveFile.writelines(r'int data_array[]{')
with open('./Sensor_1470733864.csv','r') as curFile:
		count = 0
		
		###################### delta acc data ###########################
		ltdeta = ltltdeta = curdeta = 0
		x1 = y1 = z1 = 0
		deta_arr  = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
		deta_avg = 0
		###################### delta acc data ###########################
		ltxyz = ltltxyz = curxyz = 15372
		xyz_arr = [15372, 15372, 15372]
		xyz_special = [15372, 15372, 15372, 15372, 15372]
		xyz_avg = 0
		lt_xyz_avg = 0
		special_avg = 0
		
		for lineTex in curFile:
			count += 1
			x = int(lineTex.split(',')[1],16)
			y = int(lineTex.split(',')[3],16)
			z = int(lineTex.split(',')[5],16)
			if x > 128:
				x = x-256+1
			if y > 128:
				y = y-256+1
			if z > 128:
				z = z-256+1
			x = x*4
			y = y*4
			z = z*4
			
			###################### delta acc data ###########################
			ltltdeta = ltdeta
			ltdeta = curdeta
			if (x == 64) and (y == 0) and (z == 0):
				#curdeta = deta_avg
				count -= 1
				continue
			else:
				curdeta = abs(x-x1) + abs(y-y1) + abs(z-z1)
				x1 = x
				y1 = y
				z1 = z
			
			#if (ltdeta > ltltdeta) and (ltdeta > curdeta) and ((ltdeta - ltltdeta)>100) and ((ltdeta - curdeta)>100):
			#	ltdeta = (ltltdeta+curdeta) // 2
			
			#if (ltdeta < ltltdeta) and (ltdeta < curdeta) and ((ltltdeta - ltdeta)>100) and ((curdeta - ltdeta)>100):
			#	ltdeta = (ltltdeta+curdeta) // 2
			
			deta_arr[count%2] = ltdeta
			#deta_avg = (deta_arr[0] + deta_arr[1] + deta_arr[2] + deta_arr[3] + deta_arr[4] + deta_arr[5]+deta_arr[6]+deta_arr[7]+deta_arr[8]+deta_arr[9]) // 10
			#deta_avg = (deta_arr[0] + deta_arr[1] + deta_arr[2] + deta_arr[3] + deta_arr[4]) // 5
			#deta_avg = (deta_arr[0] + deta_arr[1] + deta_arr[2]) // 3
			deta_avg = (deta_arr[0] + deta_arr[1]) // 2
			
			###################### bias acc data ###########################
			ltltxyz = ltxyz
			ltxyz = curxyz
			#if (x == 64) and (y == 0) and (z == 0):
				#curxyz = special_avg
			#	test += 1
			#else:
			curxyz = x*x +y*y +z*z
			
			if (ltxyz>ltltxyz) and (ltxyz > curxyz) and ((ltxyz-ltltxyz)>20000) and ((ltxyz-curxyz)>20000):
				ltxyz = (ltltxyz+curxyz) // 2
			
			if (ltxyz<ltltxyz) and (ltxyz < curxyz) and ((ltltxyz - ltxyz)>20000) and ((curxyz - ltxyz)>20000):
				ltxyz = (ltltxyz+curxyz) // 2
			
			#使用线性求值
			xyz_special[count%5] = ltxyz
			special_avg = (xyz_special[0] + xyz_special[1] + xyz_special[2] + xyz_special[3] + xyz_special[4]) // 5
			
			xyz_arr[count%3] = ltxyz
			xyz_avg = (xyz_arr[0] + xyz_arr[1] + xyz_arr[2]) // 3
			
			bias_avg = xyz_avg - lt_xyz_avg
			lt_xyz_avg = xyz_avg
			
			bias_xyz = curxyz - ltxyz
			
			curSaveFile.writelines(str(x)+ ','+ str(y)+ ','+ str(z)+ ','+ str(curxyz) + ',' + str(xyz_avg) + ',' + str(bias_avg) + ','+ str(curdeta) + ',' + str(deta_avg) + '\n')
			#curSaveFile.writelines(str(curxyz) + ',' + str(xyz_avg) + ',' + str(bias_xyz) + ',' + str(bias_avg) + ','+ str(curdeta) + ',' + str(deta_avg) + '\n')
			
#raw_input("input:<enter>")