# Cloud Storage Manager
This is my attempt at authoring a Hierarchical Storage Management (HSM)
filesystem layer using components mostly already present on the Linux
platform. In concept it involves the following components:
* fanotify: The file activity notification layer for Linux, which allows
for monitoring of filesystem activity and taking certain actions based upon
that activity.
* xattr: Storing of various flags and attributes relevant to the
hierarchical model within extended attributes. This, of course, requires
a filesystem that supports extended attributes and has the correct
mount options.  In particular, marking a file as a "stub" and the various
retrieval operations, as well as automating the synchronization of changed
files into the cloud are stored in extended attributes. I'm using ZFS as
my filesystem of choice, but any filesystem that supports xattrs ought to
work.

As this is my first stab at this, there are very likely to be a lot
of things wrong with this that I'm sure will be discovered along the way -
either by me, or by those of you who might chance to stumble upon this
little project of mine.

It is also worth noting that there are a few things that I'm not striving
for in this particular project. First, while I do want the system to perform
reasonably well, I'm not shooting for a high-performance filesystem. I'm not
attempting in any way to build out a filesystem that somehow magically lets
you do millions of IOPS or terrabytes per seconds transactions to the Cloud.
My primary motivation is to replace Windows-based file servers with Linux-
based ones, and have them automatically sync to the cloud for the purposes
of backup/restore and for offloading local storage to the cloud in a
transparent way.

And, before you ask, yes, I know that there are other products out there that
accomplish similar or even the same things:
* AWS Storage Gateway - Does a reaonably good job of this for a wide variety
of applications....except when it comes to Microsoft Office and Adobe Acrobat
documents. As I've attempted to use this as a NAS/Windows File Server (WFS)
replacements, I've stumbled across a couple of corner cases related to MS
Office and Adobe where SGW just does not do the job. The technical reasons
behind this are related to the fact that AWS have disabled Oplocks on the
platform (due to lack of support in S3), and adding/enabling this feature
is non-trivial.
* SoftNAS, Nasuni, etc. - Many commercial solutions exist out there for this
kind of thing, with lots of features and fancy management interfaces. These are
great, but costly, and one of the reasons I value Open Source software is for
accessibility - I want to make certain software and features available to anyone,
regardless of whether or not they can afford it.
* ProxyFS - Looks like it possibly could maybe do the job, but it's a lot of
work and setup to accomplish something that, in my opinion, ought to be
a relatively simple task. This project aims at simplicity - code, configuration,
and maintenance.
