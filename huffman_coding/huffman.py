#!/usr/bin/python
# -*- coding: utf-8 -*- 
import sys
import getopt
import Queue
import heapq
import pickle


lookup={}

def convert(string_code):
	final=""
	part=""
	size=0
	for char in string_code:
		part += char
		if(len(part) == 8):
			final += chr(int(part,2))
			size+=1
			part = ""
	if(part !=""):
		final += chr(int(part,2))
	print "length ",len(string_code)," ", size
	return final

class HuffmanNode:
	compressed = "" 
	def __init__(self, char, frequency):
		self.char = char
		self.frequency = frequency
		self.left = None
		self.right = None
	
	def __cmp__(self, other):
		if self.frequency < other.frequency:
			return -1
		elif self.frequency == other.frequency:
			return 0
		else:
			return 1

	def merge(nodeA, nodeB):
		merged = HuffmanNode(None,0)
		merged.frequency = nodeA.frequency + nodeB.frequency
		merged.left = nodeA if (nodeA.frequency < nodeB.frequency) else nodeB
		merged.right = nodeB if (nodeA.frequency < nodeB.frequency) else nodeA
		return merged
	
	def traverse(root, code):
		if root.char != None:
			lookup[root.char] = code
			print root.char," ",code
			return
		HuffmanNode.traverse(root.left, code+'1')
		HuffmanNode.traverse(root.right, code+'0')

def compress(infile, outfile):
	cmap = dict()
	size =0
	with open("sample.txt", "r") as inputfile:
		for line in inputfile:
			for ch  in line:
				size += 1 
				if ch in cmap:
					cmap[ch] = cmap[ch] + 1
				else:
					cmap[ch] = 1
	pqueue = []
	print cmap
	heapq.heapify(pqueue)
	for key in cmap:
		heapq.heappush(pqueue, HuffmanNode(key,cmap[key]))
	while len(pqueue) > 1:
		nodeA = heapq.heappop(pqueue)
		nodeB = heapq.heappop(pqueue)
		merged = HuffmanNode.merge(nodeA, nodeB)
		heapq.heappush(pqueue,merged)
	root = heapq.heappop(pqueue)
	HuffmanNode.traverse(root,'1')
#	print lookup
	compressed = ""
	with open("sample.txt", "r") as inputfile:
		for line in inputfile:
			for ch  in line:
				compressed += lookup[ch]
	print lookup
	comp = convert(compressed)
	combine = [comp, root]
	print "compressed ", len(compressed)
	print root.frequency
	output = file("output.txt", "w")
	output.write(comp)
	output.close()
	pickle.dump(root, open("pickledump.hmc","wb"))
	node =pickle.load(open("pickledump.hmc","rb"))
	print "loading:"
	HuffmanNode.traverse(node,'1')
	print len(compressed)/8


def main():
	print "hello"
	print 'Number of arguments:', len(sys.argv), 'arguments.'
	print 'Argument List:', str(sys.argv)

	operation = sys.argv[1]
	infile = sys.argv[2] 
	outfile = sys.argv[3]
	
	print operation," ",infile," ",outfile

	if int(operation) == 1:
		print "Compressing ",infile,". Output file: ", outfile
		compress(infile, outfile)
	
if __name__ == "__main__":
	main()
