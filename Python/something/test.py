from morse import decodeBitsAdvanced
from morse import decodeBits
from morse import decodeMorse

def unittest(str1, str2):
    res = decodeBitsAdvanced(str1)
    if res == str2:
        print("Correct: " + str1 + " " + str2)
    else:
        print("ERROR: "+ str1 + " => " + res + " but " + str2)

# unittest("1", ".")
# unittest("101", "..")
# unittest("1001", ". .")
# unittest("10001", ". .")
# unittest("100001", ". .")
# unittest("1000001", ". .")
# unittest("10000001", ". .")
# unittest("100000001", ". .")
# unittest("1000000001", ". .")
# unittest("10000000001", ". .")

last_signal = "111111110000000111111111111000000000001111111110000011111111101000000001111111111110110000111111110111111111110000000000000000000111111111100001100011111111111110001110000000000011111111111100001111111111000011001111111111100000000001111111111110111000011100000000000000000011111111110101111111101100000000000000011111111111000011111111111100001000011111111111111000000000001111111110000000110000001110000000000000000000000000000111100011111000001111000000001111111111001111111111001111111111111000000000111100111110111111100000000000000000000001111111111100000000111110000000111110000000011111111111100000000011111000111111110000000001111111111100000110000000001111100000001110000000000111111111111110001110011111111110011111100000000000000000000011110001111111111000011111111111111001000000000011111111001111111101111111100000000111011111110001110000000010011111110000000011111111110000000001111000011111110000000000000111111111001111111101111111111000000000001111111100000011000000000000000000001111111010100000100000011111111000000000111110001111111110000001111111111100111111110011111111100000000110001111111100001110111111111111000011111000011111111000000000000111100111011100010001111111100000000011110000111111100101100011111111110000000000000000001111111111100000001000000000000000000111101111100000010000111011100000000000111111111000000111111111111001111111111110001111111110000011111111000000000000011101111111111110000001100111111111111011100011111111111000000001111000001111000001111111111000001111111111110000000111111110000000000010000001111000000010000011111001111111111100000000000000000000100011111111000000111111111000000000000001000011111111111101110011111111111000001111111000011111111110000000000000000000000000111000001111111111110111100000000100000000111111111000111111111111000011100001111111111111000000000000001111100000111110011111111000000000000111000111000000000000111110000011111111111010000000011100000000000000000000000000001111100100000000001111111110000111111111100000000001111111111111011111111111000000000100000000000000111111111001000011000000000000001111001111000000000011000000011111111111100000000111111111110000000001111000000000000000000001111011111111111110000000000011110000111110000111100000000011001111111001110000000001001110000000000001111100000100000111110000000000000011111111111000000001101111111111000000000000001111111111111000001110000000001111111100011110000001111111101111110000000011110000000000100001111111110000111100011111111101111100001111111111110000000000000000000000001111111111100000001110111111111000111111100000000011111111100000111111111001111111100000000011111111111001111111111100000000001100000000000000000010000111111111100000000011111111100000000000000000000000111111111111110000001111111110000011111111100000000001111111100000100000000111111110000111110011111111000000011100000000111100000000010111111110000111110111111111100110111111111110000000000000000001000111111111111011111111000000000000000011000000000000000000111100101111100000000111111111000000000011111000111111111111011000000001111100000111100001111111111110000000011111111111000011101111111111101110000000000111111111011111000111111111100000000000000000000000000100001111111111000000000011111111101111100000000000000000000001100000111100000000000011111111111001100011111111000000111000000000001111100000000111111111100000111110000011110001100000000111000000000000001111000011111111111000001110000000011111111110000001111111111001100000000011110000011111111000111000011111111100000100111111111100000000000000000001111000000111110000011110000000001111110011100000000111111110001000000000000111111110000110011111111000000000001101110000000000001111111111110001000000001111111111100000011111111110111"
last_morse = decodeBitsAdvanced(last_signal)
print(last_morse)
# last_out = decodeMorse(last_morse)
