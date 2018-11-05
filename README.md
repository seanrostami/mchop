# mchop

Function ```mchop``` truncates the mantissa of a ```double``` to a given number of binary places, preserving the more significant and setting the less significant to 0. Similar to "chop" in Octave except that, despite its name, Octave's function rounds. If C99 is available, variants ```mchopf``` and ```mchopl``` are provided, which instead accept/return, respectively, ```float``` and ```long double```. If C11 is available then a type-generic version is provided.


## AUTHOR ##

[Sean Rostami](https://www.linkedin.com/in/sean-rostami-77255a141/) 


## CONTACT ##

<sean.rostami@gmail.com>
