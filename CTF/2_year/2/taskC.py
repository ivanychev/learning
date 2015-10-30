import sys

word_list = []
for line in sys.stdin:
	word_set += line.strip()
word_list.sort()
word_set = set(word_list)
for word in word_set:
	print word, word_list.count(word)
