     |      \   _ \  \   __| |  /    |     |  
     |     _ \  __/ _ \ (      <  __ __|__ __|
    ____|_/  _\_| _/  _\___|_|\_\   _|    _|  

**C++ API for the Linear Algebra PACKage**

**Innovative Computing Laboratory**

**University of Tennessee**

* * *

[TOC]

* * *

About
=====

The Linear Algebra PACKage (LAPACK) is a standard software library
for numerical linear algebra. It provides routines for solving
systems of linear equations and linear least squares problems,
eigenvalue problems, and singular value decomposition.
It also includes routines to implement the associated matrix factorizations
such as LU, QR, Cholesky, etc. LAPACK was originally written in FORTRAN 77,
and moved to Fortran 90 in version 3.2 (2008). LAPACK provides routines
for handling both real and complex matrices in both single and double precision.

The objective of LAPACK++ is to provide a convenient, performance oriented API
for development in the C++ language, that, for the most part,
preserves established conventions, while, at the same time, takes advantages
of modern C++ features, such as: namespaces, templates, exceptions, etc.

LAPACK++ is part of the project
[Software for Linear Algebra Targeting Exascale](http://icl.utk.edu/slate/)
(SLATE), which is funded by the [Department of Energy](https://energy.gov)
as part of its [Exascale Computing Initiative](https://exascaleproject.org)
(ECP).

Closely related to LAPACK++ is the
[BLAS++ project](https://bitbucket.org/icl/blaspp), which aims at providing
a C++ API for the Basic Linear Algebra Subprograms (BLAS).

* * *

Resources
=========

* Visit the [BLAS++ repository](https://bitbucket.org/icl/blaspp) for more information about the C++ API for BLAS.
* Visit the [ECP website](https://exascaleproject.org) to find out more about the DOE Exascale Computing Initiative.
* Visit the [SLATE website](http://icl.utk.edu/slate/) for more information about the SLATE project.
* Visit the [SLATE Working Notes](http://www.icl.utk.edu/publications/series/swans) to find out more about ongoing SLATE developments.
* Feel free to join the [SLATE User](https://groups.google.com/a/icl.utk.edu/forum/#!forum/slate-user) Google group by following the link and clicking *Apply to join group*. Then email your questions and comments to *slate-user@icl.utk.edu*.

* * *

Acknowledgments
===============

Funding
-------

This research was supported by the Exascale Computing Project (17-SC-20-SC),
a collaborative effort of two U.S. Department of Energy organizations
(Office of Science and the National Nuclear Security Administration)
responsible for the planning and preparation of a capable exascale ecosystem,
including software, applications, hardware, advanced system engineering
and early testbed platforms, in support of the nation's exascale computing imperative.

Cycles
------

This research uses resources of the Oak Ridge Leadership Computing Facility,
which is a DOE Office of Science User Facility supported under Contract DE-AC05-00OR22725.

* * *

License
=======

    Copyright (c) 2017, University of Tennessee
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the University of Tennessee nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL UNIVERSITY OF TENNESSEE BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
