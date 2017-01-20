from subprocess import check_output

from subprocess import STDOUT 
import subprocess
'''
try:
    output = check_output("diff actual/LexChallenge.qk.out expect/LexChallenge.qk.out", shell=True, stderr=subprocess.STDOUT)
except CalledProcessError as e:
    output = e.output
'''


files = ["GoodWalk.qk"
,"LexChallenge.qk"
,"Pt.qk"
,"Sqr.qk"
,"SqrDecl.qk"
,"TypeWalk.qk"
,"bad_break.qk"
,"bad_escape.qk"
,"bad_init.qk"
,"hands.qk"
,"not_a_duck.qk"
,"robot.qk"
,"schroedinger.qk"
,"schroedinger2.qk"]

for f in files:
    out = check_output("../scanner {1}{0} >{2}{0}.out 2>{2}{0}.err".format(f, "samples/", "actual/"), shell=True)
'''
    print("Diff'ing {}.out".format(f))
    out = check_output("diff actual/{0}.out expect/{0}.out".format(f), shell=True)
    if (out):
        print(out)
    print("Diff'ing {}.err".format(f))
    out = check_output("diff actual/{0}.err expect/{0}.err".format(f), shell=True)
    if (out):
        print(out)
'''

