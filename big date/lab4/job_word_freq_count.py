from mrjob.job import MRJob
from mrjob.step import MRStep   
import re

# A MapReduce job usually splits the input data-set into independent chunks which are processed 
# by the map tasks in a completely parallel manner. 
# The framework sorts the outputs of the maps, which are
# then input to the reduce tasks. Typically both the input
# and the output of the job are stored in a file system shared 
# by all processing nodes. The framework takes care of scheduling tasks, 
# monitoring them, and re-executing the failed tasks.


# A mapper takes a single key and value as input, and 
# returns zero or more (key, value) pairs. The pairs 
# from all map outputs of a single step are grouped by key.

# A combiner takes a key and a subset of the values for 
# that key as input and returns zero or more (key, value) 
# pairs. Combiners are optimizations that run immediately 
# after each mapper and can be used to decrease total 
# data transfer. Combiners should be idempotent (produce 
# the same output if run multiple times in the job pipeline).

# A reducer takes a key and the complete set of values for that 
# key in the current step, and returns zero or more arbitrary 
# (key, value) pairs as output.

# After the reducer has run, if there are more steps, 
# the individual results are arbitrarily assigned 
# to mappers for further processing. 
# If there are no more steps, the results are sorted and made available for reading.

WORD_RE = re.compile(r"[\w']+")

class MRWordFreqCount(MRJob):

    def __init__(self, *args, **kwargs):
        super(MRWordFreqCount, self).__init__(*args, **kwargs)
        self.count_top_k = 0
        self.top_k = 15


    def steps(self):
        return [
            MRStep(mapper=self.mapper_get_words,
                   combiner=self.combiner_count_words,
                   reducer=self.reducer_count_words),
            MRStep(mapper=self.map_reverse,
                reducer=self.reducer_reverse),
            MRStep(reducer=self.reducer_top_k),
        ]

    def mapper_get_words(self, key, line):
        # yield each word in the line
        for word in WORD_RE.findall(line):
            yield (word.lower(), 1)

    def combiner_count_words(self, word, counts):
        # optimization: sum the words we've seen so far
        yield word, sum(counts)

    def reducer_count_words(self, word, counts):
        yield word, sum(counts)

    def map_reverse(self, word, count):
        yield -count, word

    def reducer_reverse(self, count, word):
        for w in word:
            yield -count, w

    def reducer_top_k(self, count, word):
        if self.count_top_k > self.top_k:
            return 
        self.count_top_k += 1
        yield count, [w for w in word]


if __name__ == '__main__':
    MRWordFreqCount.run()