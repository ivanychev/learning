from IPython.lib import passwd
hsh = passwd()
with open('hash.txt', 'w') as f:
    f.write('hash=%s\n' % hsh)
