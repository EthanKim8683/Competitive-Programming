# README

## What happened

I wanted to put my new competitive programming files onto GitHub, but left some files out of my .gitignore. I fixed it, but then I still had some files that were just untracked.

I looked on StackOverflow for some answers and somebody said to `git rm` everything (not `git rm --cached`, to be clear) and since I didn't know git that well I just went ahead and did it. Huge mistake.

A couple MB of hand-written competitive programming solutions just completely disappeared. And I didn't realize it until quite a bit later too because it left a few of the files in the main directory---enough to think everything was okay---but actually everything was gone, including my custom tools and snippets library.

So I'm rewriting everything from scratch. The snippets I might steal from some old solutions, but my CLI tool I have to rewrite completely.

## Lessons I learned while making this

I didn't realize just how debilitating my obsessiveness was until now.

I think last time I made my CLI tool, I really focused on making something that worked, rather than something that was perfect? This time I was starting fresh and felt like I was responsible for making the best CLI tool I could.

But there were so many problems. The biggest one being that Darwin doesn't seem to enforce a lot of the more niche features of Unix, especially when it comes to resource management. I spent a lot of time trying to work around these problems, but at the end of the day, it just made my code so much more complicated and cluttered than it needed to be.

To combat these things, I've found the following pretty helpful:
- Planning ahead: I notice that when I don't plan, I get lost in "improving things". Like I find something that looks cool and almost always end up spending hours implementing or understanding it without considering whether I actually need it.
- Listening to music while coding: It muddles my brain enough to prevent me from being perfectionist-y. Like if I'm ever trying to make something perfect, the music makes it really hard to think too much and I'm reminded to stick to what's necessary.

## Things I stick to

- Errors are if CPT itself errors (that way anything can throw an error without triggering something it needn't), otherwise, return `success` and `errors` properties
- Aim for the simplest possible solution. That way the project won't get cluttered in the future with things we don't need.
- Don't consider the future too much. Considering the future is for planning. If you consider the future while designing, you'll get lost in the possibilities without improving what's in front of you.
