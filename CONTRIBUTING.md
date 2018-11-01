# Contributing

If you are not a member of NoneOfAllOfTheAbove we encourage you to fork this repo and eventually submit pull requests.

## Regarding the team

### Organization

Keep in mind the name of the branch you are associated to.  

Member | Branch
--- | --- |
Arielle| `nn-training`
Ferdinand | `gui`
Louis| `improve-preprocessing`
Theo| `improve-segmentation`

### Workflow

At the beginning (if you use git in the terminal):
1. Configure the connection to github.com by [refering to this](https://help.github.com/articles/connecting-to-github-with-ssh/).
2. `git config --global user.name [your first name]`  
`git config --global user.email [mail adress used on github.com]`
3. `git clone git@github.com:NoneOfAllOfTheAbove/OCR.git --branch [your branch]` *(see above for branch name)*

Before working:
1. Make sure you are working on your branch: `git branch`
2. Pull potential modifications (especially if you work on a branch with collaborators): `git pull`

After each significant modification:
1. `git status`
2. `git add *`
3. `git commit -m "Well detailed message."`
4. `git push`

### Rules

1. Respect the book of specifications (work on Linux, code guidelines...).
2. Push only on your corresponding branch.
3. Do commit regularly and describe what you have done in the commit message.
4. Your functions must be put inside a separate .c file (with its corresponding .h file) and called from main.c.