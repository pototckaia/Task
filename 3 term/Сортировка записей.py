def get_key(type_v, value):
    return {
        'd': float,
        'i': lambda x: -1 * int(x),
        'u': int,
        'c': lambda x: -1 * ord(x),
        's': str
    }.get(type_v)(value)


with open('input.txt', 'r') as fin:
    n, m = map(int, fin.readline().split())
    types = fin.readline().split()
    priority_fields = list(map(int, fin.readline().split()))
    dates = [fin.readline().rstrip('\n') for i in range(n * m)]

fields = []
for i in range(0, n):
    fields.append([])
    fields[i].append(i)
    fields[i].extend([{'prior': priority_fields[k], 'key': get_key(types[k], dates[k + i * m])} for k in range(0, m)])
    fields[i][1:] = sorted(fields[i][1:], key=lambda x:x['prior'], reverse=True)

fields = sorted(fields, key=lambda x: tuple(x[i]['key'] for i in range(1, m+1)))

with open('output.txt', 'w') as fout:
    fout.write('\n'.join(str(field[0]) for field in fields))

