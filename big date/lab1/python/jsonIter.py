class JsonIterator:
    def __iter__(self):
        return self

    def __init__(self, fileName):
        self.isEnd = False
        self.file = open(fileName, 'rb')

        self.skipSpace()
        self.isEnd = self.file.read(1) != b'['
        self.skipSpace() 

    def __next__(self):
        f = []
        if self.isEnd:
            self.file.close()
            raise StopIteration
        self.skipSpace();
        self.file.read(1) # begin frame'['
        
        while self.getPeek() != b']':
            f.append(self.getListInt())
            self.skipSpace(b',')
        
        self.file.read(1) # end frame - ']'
        self.skipSpace(b',')

        self.isEnd = self.getPeek() == b']'
        return f


    def skipSpace(self, c = b' '):
        while self.getPeek().isspace() or self.getPeek() == c:
            i = self.file.read(1)

    def getInt(self):
        i = 0
        while self.getPeek().isdigit():
            i = 10*i + int(self.file.read(1))
        return i

    def getPeek(self):
        next_byte = self.file.read(1)
        self.file.seek(-1,1)
        return next_byte


    def getListInt(self):
        a = []
        self.skipSpace()
        if self.getPeek() != b'[':
            return a
        self.file.read(1)

        while self.getPeek() != b']':
            self.skipSpace(b',')
            a.append(self.getInt())
        self.file.read(1)
        return a