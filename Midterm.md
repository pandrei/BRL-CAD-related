# Object-oriented C++ Geometry API
<br/>
## Summary Overview 

I have been working on this project, as part of [Google Summer of Code](https://developers.google.com/open-source/soc/?csw=1) program. My initial proposal was to implement  the interfaces for [sph](https://github.com/pandrei/BRL-CAD-related/blob/master/Midterm.md#sph), [sketch](https://github.com/pandrei/BRL-CAD-related/blob/master/Midterm.md#sketch) and [extrude](https://github.com/pandrei/BRL-CAD-related/blob/master/Midterm.md#extrude) primitives. So far, I have completed the one for [sph](https://github.com/pandrei/BRL-CAD-related/blob/master/Midterm.md#sph) and I expect to finish the [sketch](https://github.com/pandrei/BRL-CAD-related/blob/master/Midter.md#sketch) in the following 
couple of days. By the time I will have finished [sketch](https://github.com/pandrei/BRL-CAD-related/blob/master/Midterm.md#sketch) I would have written about 1500 - 2000 lines of code,most of them consisting in headers(the interface design) and actual implementantion (matching C++ file with the actual classes and methods behaviour implemented). My estimation is that the total number of lines proposed until
mid-term would be around 3000.
<br/>
<br/>

C++ Geometry API relies internally on BRL-CAD primitives library(named librt) for data handling, as such, everything is 
stored in the structures provided by BRL-CAD, what the interface actually does is offer a much more convenient
way of using it, OOP. OOP has been maintream programming paradigm for a decade if not more.

<br/>
The main purpose of this API is to make writing application using BRL-CAD simpler and more powerful
because one could just use the API according to it's description, without actually knowing every implementation
detail under the hood(think Java!).

## Class overview
<br/>
<br/>

Sphere is an object that is similar to Ellipsoid, as such the code does not differ too between them.
On the other hand, Sketch relies on several subclasses to handle different types of segments that make a curve.
Below, we can find an UML diagram of the class relationship so far. If you re not familiar with UML, the arrow
with the black diamond implies contention. One Sketch contains multiple(zero or more) of each type.

![class diagram](http://i.imgur.com/QcA6B6P.png)

## Conclusion

The combined factors of my slow start(lack of activity for first two weeks) and the difficulty of C++ caused the
overall progress to be less than what I had initially planned. By C++ difficulty, I'm implying knowing and understanding
the best practices involved. I've been enjoying this project as it's centered around class design, one of the most
difficult concepts to grasp as a student/fresh graduate and while my work progress has not met my expectations, 
my personal improvement has greatly exceeded them. I don't know how realistic this is, but I certainly hope that I can
catch up until the end and finish as planned, constantly improving the depth of my OOP concepts understanding.



## Technical details

Below, you can find the links to the patch tickets on Sourceforge as well as my development log.
The patch tickets offer a better insight of the development course(in detail) while the development logs
serve more like a journal.
[Sphere](https://sourceforge.net/p/brlcad/patches/279/) <br/>

[Sketch](https://sourceforge.net/p/brlcad/patches/280/) <br/>

[Development logs](http://brlcad.org/wiki/User:Popescu.andrei1991/devlogs2014) <br/>

[Initial proposal](https://www.dropbox.com/s/9zgki85xmy6w02f/Popescu_Andrei_proposal_latest.pdf) <br/>


#sph
Sphere, special case of the ellipsoid, with vectors A B and C all the same magnitude (radius).
![sph img](http://brlcad.org/w/images/0/02/Union_sph.png =150x150)
<br/>
#sketch
2d outline
<br/>
#extrude
Extrusion of a 2-d sketch
<br/>
