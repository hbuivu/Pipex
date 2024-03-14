# pipex

## Concepts
Unix process, pipe, dup, fork, execve, wait, heredoc, redirections

## Execution
./pipex file1 cmd1 cmd2 file2  
the command should act like the following:  
`./pipex infile "ls -l" "wc -l" outfile` should behave like `< infile ls -l | wc -l > outfile`  
`./pipex infile "grep a1" "wc -w" outfile` should behave like `< infile grep a1 | wc -w > outfile`  

## Bonus
* Redirections
* Heredoc
`./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2` should behave like `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`  
` ./pipex here_doc LIMITER cmd cmd1 file` should behave like `cmd << LIMITER | cmd1 >> file`  
