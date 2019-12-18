'''
c * x -> max
Ax <= b
x >= 0



A неотрицательная 8x6
b неотрицательны

 Ищется оптимальноерешение  (симплекс-метод), 
 В двойственнойзадаче  ищется допустимое  и оптимальное рещения.
'''
import numpy as np
import math

def first_iteration(data): 
    extended_factories = len(data['B'])
    nullArr = []
    for j in range(extended_factories):
        nullArr.append(0)
    matrixArr = []
    for j in range(extended_factories):
        resourses = []
        for k in range(len(data['A'][j])):
            resourses.append(int(data['A'][j][k]))
        ones = np.zeros((3, 3), int)
        np.fill_diagonal(ones, 1)
        matrixArr.append([int(data['B'][j])] + resourses + ones[j].tolist())
    relations = []
    number_of_lead_column = data['C'].index(str(min(map(int,data['C']))))
    lead_column_elements = []
    for o in range(len(matrixArr)):
        lead_column_elements.append(matrixArr[o][number_of_lead_column+1])
    for l in range(len(lead_column_elements)):
        try:
            relations.append(int(int(data['B'][l])/lead_column_elements[l]))
        except ZeroDivisionError:
            relations.append(float('inf'))
    y = []
    for j in range(len(data['B'])):
        y.append(str(j + len(data['C']) + 1))
    new_data = 
    	{'B': data['B'],
    	 'C': [0] + list(map(int,d['C'])) + nullArr,
    	 'A':matrixArr,
    	 'Relations':relations,
    	 'y':y
    	 }
    print('Первая матрица:')
    print_table(new_data)
    return new_data

def iteration(data):
    relations = []
    number_of_lead_column = data['C'].index(min(data['C']))
    lead_column_elements = []
    for o in range(len(data['A'])):
        lead_column_elements.append(data['A'][o][number_of_lead_column])
    for l in range(len(lead_column_elements)):
        try:
            relations.append(float(float(data['B'][l])/lead_column_elements[l]))
        except ZeroDivisionError:
            relations.append(float('inf'))
    number_of_lead_row = relations.index(min(relations))
    lead_element = float(data['A'][number_of_lead_row][number_of_lead_column])
    print('Разрешающий элемент:' + str(lead_element) + ' на позиции ' + str(number_of_lead_row) + ',' + str(number_of_lead_column) + '\n') 
    print('Замена базиса: ' + data['y'][number_of_lead_row] + ' out, ' + str(number_of_lead_column) + '<-in\n')
    data['y'][number_of_lead_row] = str(number_of_lead_column)
    print('y = '+(',').join(data['y']))
    print('Меняю матрицу\n')
 
    for i in range(len(data['C'])):
        if i !=number_of_lead_column:
            A=data['A'][number_of_lead_row][i]
            B=data['C'][number_of_lead_column]
            print('Элемент '+str(data['C'][i])+' из вектора С под номером '+str(i+1)+' -> ',end='')
            data['C'][i]=data['C'][i]-((A*B)/lead_element)
            print(data['C'][i])
    #lead column c element
    data['C'][number_of_lead_column]=0.0
    #main elements
    a_basic=data['A']
    for i in range(a_basic.__len__()):
        for j in range(a_basic[i].__len__()):
            num = a_basic[i][j]
            if i!=number_of_lead_row and j!=number_of_lead_column:
                A=a_basic[i][number_of_lead_column]
                B=a_basic[number_of_lead_row][j]
                num_old=num
                num=num-(A*B)/lead_element
                print('Элемент '+str(num_old)+' на позиции '+str(i)+','+str(j)+' -> '+str(num))
                data['A'][i][j]=num
    data['A'][number_of_lead_row][number_of_lead_column]=1.0
    print('Разрешающий элемент:'+str(lead_element)+' на позиции '+str(number_of_lead_row)+','+str(number_of_lead_column)+' -> 1 ')
 
    #lead row
    for i in range(2,data['A'][number_of_lead_row].__len__()):
        try:
            print('Элемент '+str(data['A'][number_of_lead_row][i])+' на позиции '+str(number_of_lead_row)+','+str(i)+' -> ',end='')
            data['A'][number_of_lead_row][i]=a_basic[number_of_lead_row][i]/lead_element
 
        except ZeroDivisionError:
            data['A'][number_of_lead_row][i]=float('inf')
        print(data['A'][number_of_lead_row][i])
    #lead column
    for j in range(data['A'].__len__()):
        if(j!=number_of_lead_row):
            print('Элемент '+str(data['A'][j][number_of_lead_column])+' на позиции '+str(j)+','+str(number_of_lead_column)+' -> 0')
            data['A'][j][number_of_lead_column]=0
 
    print('Элемент '+str(data['A'][number_of_lead_row][0])+' на позиции '+str(number_of_lead_row)+','+str(0)+' -> ',end='')
    #lead row first element
    data['A'][number_of_lead_row][0]=float(a_basic[number_of_lead_row][0])/lead_element
    print(data['A'][number_of_lead_row][0])
    for k in range(data['B'].__len__()):
        data['B'][k]=data['A'][k][0]
 
 
    #relations
    relations=[]
    number_of_lead_column = data['C'].index(min(data['C']))
    lead_column_elements=[]
    for o in range(data['A'].__len__()):
        lead_column_elements.append(data['A'][o][number_of_lead_column])
    for l in range(lead_column_elements.__len__()):
        try:
            relations.append(float(float(data['B'][l])/lead_column_elements[l]))
        except ZeroDivisionError:
            relations.append(float('inf'))
    data['Relations']=relations
    return data


def extract_result(data, max_numbers):
    print("Максимальный результат  " + str(data["C"][0]))
    print("При:")
    
    y_numbers_used = []
    for i in range(len(data['y'])):
        if int(data['y'][i]) <= len(data['y']):
            y_numbers_used.append(int(data['y'][i]))
            print("X" + str(data['y'][i])+" = "+ str(data['B'][i]))
    print("Проверка:")
    result = 0
    check_str = ''
    for i in y_numbers_used:
        result += data['B'][data['y'].index(str(i))] * float(max_numbers[i-1]) * (-1)
        check_str += str(data['B'][data['y'].index(str(i))]) + "*" + str(float(max_numbers[i-1]) * (-1)) + "+"
    check_str = check_str[:-1]
    print(check_str+'='+str(result))

if __name__ == '__main__':
    
    d = {
    	'A' : [['2', '3', '1'], 
    			['4', '2', '2'], 
    			['2', '1', '2']], 
    	'C': ['5', '-2', '-3'], 
    	'B': ['10', '12', '8']
    	}
    
    n = first_iteration(d)
    while min(n['C']) < 0:
        n = iteration(n)
            
    extract_result(n, d['C'])