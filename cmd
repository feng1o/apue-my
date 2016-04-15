Script started on Tue 12 Apr 2016 09:44:28 AM CST
bash: 1=\[\e[35m\][\[\e[32m\]\[\e[32m\]\#-\[\e[32m\]\u@\[\e[31m\]\h\[\e[35m\] \W]\$ \[\e[m\]: command not found
]0;root@localhost:/home/apue-my[?1034h[35m[[32m[32m1-[32mroot@[31mlocalhost[35m apue-my]# [mls
[0m[34;42madvio-chp14[0m          [01;34mdaemons-chp13[0m  [01;34mipc-chp15[0m                [01;34mstdio-chp5[0m       wgit
[34;42mapue.3example[0m        [01;34mdatafiles[0m      [01;34mlib[0m                      [01;34mthreadctl-chp12[0m
[01;34mchp3-file-io[0m         [01;34menviron[0m        [01;31mpauesrc.3e.tar.gz[0m        [01;34mthreads[0m
[01;34mchp4-file-directory[0m  git.sh         [01;34mprocessrelationsip-chp9[0m  [01;34mthreads-chp11[0m
cmd                  [01;34mipc2[0m           [01;34msignals-chp10[0m            time
[m]0;root@localhost:/home/apue-my[35m[[32m[32m2-[32mroot@[31mlocalhost[35m apue-my]# [mcat git.sh 
#!/bin/bash
echo "git operation.........."

echo "xx $#"

if [ $# -gt 1 ]
then
    echo 'input error'
    exit 
fi

if [ $1 = 'push' ]
then
    echo 'push,please input the messages  for discriping your commit'
    read  msgcommit
    git  add -A
    git commit -m  ${msgcommit}
    git push origin master
else 
    echo 'pull'
    git pull origin master
fi
]0;root@localhost:/home/apue-my[35m[[32m[32m3-[32mroot@[31mlocalhost[35m apue-my]# [mc at git.sh  -n
     1	#!/bin/bash
     2	echo "git operation.........."
     3	
     4	echo "xx $#"
     5	
     6	if [ $# -gt 1 ]
     7	then
     8	    echo 'input error'
     9	    exit 
    10	fi
    11	
    12	if [ $1 = 'push' ]
    13	then
    14	    echo 'push,please input the messages  for discriping your commit'
    15	    read  msgcommit
    16	    git  add -A
    17	    git commit -m  ${msgcommit}
    18	    git push origin master
    19	else 
    20	    echo 'pull'
    21	    git pull origin master
    22	fi
]0;root@localhost:/home/apue-my[35m[[32m[32m4-[32mroot@[31mlocalhost[35m apue-my]# [mwc cat git.sh  -n[C[1P[1P[1P[1@w[1@c[C[1@ 
wc: invalid option -- 'n'
Try `wc --help' for more information.
]0;root@localhost:/home/apue-my[35m[[32m[32m5-[32mroot@[31mlocalhost[35m apue-my]# [mwc  git.sh  -n[C[Ks
wc: invalid option -- 's'
Try `wc --help' for more information.
]0;root@localhost:/home/apue-my[35m[[32m[32m6-[32mroot@[31mlocalhost[35m apue-my]# [mwc  git.sh  -s[Kc
357 git.sh
]0;root@localhost:/home/apue-my[35m[[32m[32m7-[32mroot@[31mlocalhost[35m apue-my]# [mei[Kxit
exit

Script done on Tue 12 Apr 2016 09:44:57 AM CST
