import re
from collections import Counter 

with open('input.txt','r') as  file_in:
    text = file_in.read().lower()
    
l = re.findall(re.compile(r'\w+'), text)

dct = Counter(l)


with open('output.txt', 'w') as file_out:
    for key in  sorted(dct.keys()):
        file_out.write(key + ' ' + str(dct[key]) + '\n')