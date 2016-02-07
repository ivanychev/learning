#!/usr/bin/python

MORSE_CODE = {'A': '.-',     'B': '-...',   'C': '-.-.',
        'D': '-..',    'E': '.',      'F': '..-.',
        'G': '--.',    'H': '....',   'I': '..',
        'J': '.---',   'K': '-.-',    'L': '.-..',
        'M': '--',     'N': '-.',     'O': '---',
        'P': '.--.',   'Q': '--.-',   'R': '.-.',
     	'S': '...',    'T': '-',      'U': '..-',
        'V': '...-',   'W': '.--',    'X': '-..-',
        'Y': '-.--',   'Z': '--..',

        '0': '-----',  '1': '.----',  '2': '..---',
        '3': '...--',  '4': '....-',  '5': '.....',
        '6': '-....',  '7': '--...',  '8': '---..',
        '9': '----.'
        }
MORSE_CODE = {v: k for k, v in MORSE_CODE.items()}

import collections
import scipy.cluster
import numpy
import operator

def isclose(a, b, rel_tol=1e-09, abs_tol=0.0):
    return abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)

def printNext(morseCode): # prints next character
    ret = ""
    if morseCode[0] == ' ':
        ret = ' '
    else:
        ret = MORSE_CODE[morseCode.split(' ', 1)[0]]
    return ret

def getNext(morseCode):    # gets index of the next word beginning
    if morseCode[0] == ' ':
        return 2           # length of '  '
    else:
        return len(morseCode.split(' ', 1)[0]) + 1

def decodeMorse(morseCode):
    morseCode = morseCode.strip()
    ret = ""
    while morseCode != "":
        ret += printNext(morseCode)
        morseCode = morseCode[getNext(morseCode):]
    return ret

def cutZeros(signal):
    begin = signal.find('1')
    end = -signal[::-1].find('1') - 1 + len(signal)
    return signal[begin:end + 1]

def getDotLength(signal):
    chars = signal.replace('0', ' ').split() + signal.replace('1', ' ').split()
    lengths = [len(x) for x in chars]
    dot = sorted(collections.Counter(lengths).keys())[0]
    return dot

WORD_SEP = 7
CHAR_SEP = 3
DASH_LEN = 3

def labelUniqueListObjects(l):
    counter = None
    if len(l) == 0:
        return []
    ret = []
    for idx, val in enumerate(l):
        if counter is None:
            counter = 0
            ret.append(counter)
            continue
        if val in l[:idx]:
            ret.append(ret[l[:idx].index(val)])
        else:
            counter += 1
            ret.append(counter)
    return ret


def decodeBits(signal):
    signal = cutZeros(signal)
    unit = getDotLength(signal)
    signal = signal.replace(unit * '0', '0')
    signal = signal.replace(unit * '1', '1')
    signal = signal.replace('0' * WORD_SEP, '   ')
    signal = signal.replace('0' * CHAR_SEP, ' ')
    signal = signal.replace('1' * DASH_LEN, '-')
    signal = signal.replace('1', '.')
    morseCode = signal.replace('0', '')
    return morseCode

def normalizeLens(lens):
    return [float(x) for x in lens] if len(lens) > 3 else 2 * [float(x) for x in lens]

def getInitPoints(lens):
    dLens = collections.Counter(lens)
    FreqSorted = sorted([[size, quant] for size, quant in dLens.iteritems()],
                                            key = lambda x: -x[1])
    # print(FreqSorted)
    if len(FreqSorted) == 1:
        return 1, [FreqSorted[0][0]]
    return 2, [FreqSorted[0][0], FreqSorted[1][0]]
    # ret = [].append(FreqSorted[0][0])
    # lenFreqSorted = len(FreqSorted[1:])
    # for i, x in enumerate(FreqSorted[1:]):
    #     if i == lenFreqSorted - 1:
    #         return 1, ret
    #     if abs(x[0] - ret[0][0]) > 1:
    #         return 2, ret.append(x[0])


def analyzeTokens(signal):
    tokens = signal.replace("01", "0 1").replace("10", "1 0").split()
    lens = sorted([len(token) for token in tokens])
    float_lens = normalizeLens(lens)

    # print(float_lens)
    quant, initPoints = getInitPoints(float_lens)
    # print(quant, initPoints)
    try:
        ans = scipy.cluster.vq.kmeans2(numpy.asarray(float_lens), numpy.asarray(initPoints), missing='raise')
        isOneCluster = False if quant != 1 else True
    except:
        ans = scipy.cluster.vq.kmeans2(numpy.asarray(float_lens), numpy.asarray([initPoints[0]]))
        isOneCluster = True

    draft = collections.Counter(zip(lens, ans[1])).keys()
    ret = sorted(draft)
    if ret[0][1] == 1:
        ret = [[x[0], 0] if x[1] == 1 else [x[0], 1] for x in ret]

    # deal with concerns if smth is dot or DASH_LEN

    if not isOneCluster:
        mean = round((ans[0][0] + ans[0][1])/2)
        print("mean " + str(mean))
        for i, v in enumerate(ret):
            if isclose(v[0], mean):
                ret[i] = (ret[i][0], 0)

    # done with two basic clusters
    # need to deal with 7-unit pauses
    print(ans[0])
    means = sorted(ans[0])
    if not isOneCluster:
        long_border = min([means[0] * 5.5,
                           means[1] * 2])
    else:
        long_border = ans[0][0] * 5
    print(long_border)
    ret = [[x[0], x[1]] if x[0] < long_border else [x[0], 2] for x in ret]

    return dict(ret)

def advancedGetNextToken(signal):
    if len(signal) == 0:
        return -1
    base = '0' if signal[0] == '0' else '1'
    i = 0
    while i < len(signal) and signal[i] == base: i += 1
    if i == len(signal): return [signal, ""]
    return [signal[:i], signal[i:]]

ONES = {0:'.', 1:'-'}
ZEROS = {0:'', 1:' ', 2:'   '}
BITS = {'0':ZEROS, '1':ONES}

def decodeBitsAdvanced(signal):
    signal = cutZeros(signal)
    print(signal)
    if len(signal) == 0:
        return ""
    types = analyzeTokens(signal)
    print(types)
    token = None
    ret = ""
    while signal != "":
        token, signal = advancedGetNextToken(signal)
        charDict = ONES if token[0] == '1' else ZEROS
        ret += charDict[types[len(token)]]
    return ret
