# Git Branching Conventions

## 0. Guidelines
* Main is the trunk of the repo.
* Modification of main will only be done through pull requests or emergency changes.
* All other changes requires a new branch and associated issue to be created.

## 1. Create New Issue
* Create a specific and descriptive title.
* In description: 
    - Describe specific implementation instructions.
    - Include any locations in codebase requiring modification.
    - Include any useful details or advisory.
    
## 2. Create New Branch For Issue
* Branch naming: **issue type/issue-#/issue name**
* E.g. **docs/issue-1/guide-subdirectory**
* Create branch off of branch main.

## 3. Create Pull Request
* Once changes to the branch are complete, it must be pushed to origin.
* It should be ready to merge with main.
* A pull request must be created **before** merging.
    - Description must include specific changes and locations made to the codebase.


## 4. Merging Branch
* Branch merges are to be executed by **authorized members only**.