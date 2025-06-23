import os,sys
base_path = os.path.split(os.path.realpath(__file__))[0]
lib_path = os.path.join(base_path, 'lib')
sys.path.append(lib_path)
print(lib_path)

from pyd_journal import *