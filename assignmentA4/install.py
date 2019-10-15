import os

sudoPasswd = '1379'
os.system('echo ' + sudoPasswd + ' | sudo -S apt-get install nasm')
#os.system('rm install.py')
os.system('rm nasm-2.13.03-0.fc24.x86_64.rpm')
