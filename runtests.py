from subprocess import Popen, PIPE
from os import listdir, path
from functools import total_ordering

@total_ordering
class NameOrder(object):
	def __init__(self, value):
		self.value = value
	def __eq__(self, other):
		return self.value == other.value
	def __lt__(self, other):
		firstNumber, sep, firstEnding = self.value.partition(".")
		firstNumber = firstNumber.partition("/")[2]
		secondNumber, sep, secondEnding = other.value.partition(".")
		secondNumber = secondNumber.partition("/")[2]
		if (firstEnding != secondEnding):
			if ("scan" in firstEnding):
				return True
			if ("scan" in secondEnding):
				return False
			if ("eval" in firstEnding):
				return False
			if ("eval" in secondEnding):
				return True
			return firstEnding > secondEnding
		else:
			return int(firstNumber) < int(secondNumber)

files = sorted(["tests/" + f for f in listdir('tests') if path.isfile("tests/" + f) and f.endswith(".calc")], key=NameOrder)

for f in files:
	infile = open(f, 'r')

	flags = []
	if (f.endswith('.eval.calc')):
		flags += ['-e']
	elif (f.endswith('.scan.calc')):
		flags += ['-s']

	print("./calculator " + " ".join(flags + [""]) + "< " + f + ":")
	p = Popen(["./calculator"] + flags, stdin=infile, stdout=PIPE, stderr=PIPE)
	(out, err) = p.communicate()

	if (err):
		print(err.decode("utf-8"))
	elif (out):
		print(out.decode("utf-8"))
	else:
		print("No output.\n")
