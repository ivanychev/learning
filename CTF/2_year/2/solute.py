#!/usr/bin/python3.4

verify_arr = [193, 35, 9, 33, 1, 9, 3, 33, 9, 225]
user_arr = []

for n in verify_arr:
	user_arr.append(((n ^ 111) >> 5 | (n ^ 111) << 3) & 255)

password = "".join(map(chr, user_arr))
print(password)

"""
i_are_a_pyeval_mastermind
"""