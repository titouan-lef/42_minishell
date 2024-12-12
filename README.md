# Git commands
## Branch
See all branches (and what is the current branch)
```bash 
git branch
```
Create a new branch
```bash
git branch <name>
```
Switch to a branch
```bash
git checkout <branch>
```
## Update your branch with current main
Switch to your branch (if you are on another) and push
```bash
git push
```
Fetch and merge (pull) branch main on your branch
```bash
git pull origin main
```
## Push
[Update your branch with current main](#update-your-branch-with-current-main)

Fix conflict (with commit and push)

Run unit test (and fix them if necessary with commit and push)

Switch to main
```bash
git checkout main
```
Merge your work in main
```bash
git merge <branch>
```
Push modification
```bash
git push
```
