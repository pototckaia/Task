import jsonIter as ji

class Model(object):
    @property
    def cols(self):
        return 3

    @property
    def rows(self):
        return 3

    @property
    def iter(self):
        fileName = "../lab1.json"
        return ji.JsonIterator(fileName)
    
