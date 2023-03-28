# Lab 4 assignment

**Points**: 1

**Deadline**: Week 5

**Last chance deadline and penalties**: Week 7, -0.3 points / week delayed

----

Continue working on the application from the previous assignment. Push your project to this repository.

You will need to:
- Add unit tests for the two non-CRUD functionalities from the previous assignments. You might want to google for a "mocking library" in your language and framework of choice. This is usually how it's done, but if you can't find anything relevant, then search for how to do unit testing in your framework.  
    - We use the term "unit tests" loosely here: you might find them called something else in various documentations. We just care about testing our models and endpoints automatically, from the same app (without any external tools or apps, so things like Selenium are not allowed).  
- Create an account on https://aws.amazon.com/free/ or https://cloud.google.com/free (or equivalent) and deploy your project to a virtual machine. Your application should be usable by anyone with a link to it. You do not need to worry about security and performance at this point. Make sure to shut down your VM when you're not using it, so that you don't waste your resources.  
    - Note that Google Cloud gives you `300$` in credits, allowing you to use more resources. Since you will only need to run the VM while you work on it and during the labs, this is way more than enough. Depending on your tech stack choices you may or may not need more than the `1 GB` of RAM available to you in the free tier instances.  
    - Make sure that you add at least `30 GB` of storage to your VM.  
    - You must use a remote server that you can SSH into. You are not allowed to use local VMs and you are not allowed to use your own home server.
- Add at least `3` validation rules. They can be spread across multiple entities.
- Continue tracking your tasks on Trello (or equivalent). Also track the estimated time (write it before starting the task) and the actual time to completion (write it after finishing the task). Reference the tasks numbers in your commit messages.

Recall that raw SQL queries are still not allowed.
