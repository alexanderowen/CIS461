from subprocess import check_output

from subprocess import STDOUT 
import subprocess

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
    out = check_output("./scanner {1}{0} >{2}{0}.out 2>{2}{0}.err".format(f, "samples/", "actual/"), shell=True)

