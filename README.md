# OCR



## Usage

1. Clone this repository with `git clone git@github.com:NoneOfAllOfTheAbove/OCR.git`.
2. Compile the project by running the command `make` in the project folder.
3. Execute the program with `./OCR`.


## Regarding the team

### Organization

Keep in mind the name of the branch you are associated to.  

Member | Branch
--- | ---
Arielle| `character-recognition`
Ferdinand | `character-recognition`
Louis| `character-detection`
Theo| `master`

### Workflow

At the beginning (if you use git in the terminal):
1. Configure the connection to github.com by [refering to this](https://help.github.com/articles/connecting-to-github-with-ssh/).
2. `git config --global user.name [your first name]` and `git config --global user.email [mail adress used on github.com]`
3. `git clone git@github.com:NoneOfAllOfTheAbove/OCR.git`
4. Go inside the repository folder and initalize git with 'git init'.
5. `git remote add origin git@github.com:NoneOfAllOfTheAbove/OCR.git`
6. `git branch [your branch]`
7. `git checkout [your branch]`

Make sure you are working on your branch:  
View your current branch with `git branch`.  
Switch to your branch with `git checkout [your branch]`. 

After each significant modification:
1. `git add *`
2. `git commit -m "Well detailed message."`
3. `git push origin [your branch]` *(see above)*

### Rules

1. Respect the book of specifications (work on Linux, code guidelines...).
2. Push only on your corresponding branch (the branch with the name of the feature you are working on, refer to the list of branches).
3. Do commit regularly and describe what you have done in the commit message.