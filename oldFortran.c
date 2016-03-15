//
//  oldFortran.c
//  feffsphere2
//
//  Created by Alexander Kompch on 11.03.16.
//  Copyright (c) 2016 Alexander Kompch. All rights reserved.


1  !Modules with DATA DECLARATIONS
2
3  module Main
4                  character*8, parameter :: VERSION = '151013a '
5  end module Main
6
7
8  module Global
9          integer, parameter :: DIM=3                                             !dimension DIM=3 means x,y,z positions
10          integer :: i, j, k                                                              !loop counters
11          integer :: iostat, status
12
13          real, dimension(:,:), allocatable :: pos, newpos                !atom positions
14          real, dimension(:), allocatable :: rpos
15          integer, dimension (:), allocatable :: typ, newtyp              !atom type
16          character*2, dimension(:), allocatable :: chartyp
17
18          real :: dia                                                                             !sphere diameter
19
20          integer :: tot, atno                                                    !total number of atoms, atom number at center of sphere (atno)
21
22          character*80 :: filein, fileoutfeff                             !filename for input structure and output structures
23          character*80 :: fileoutcoo, fileoutxyz, fileoutpdb
24          character*80 :: dummy                                                   !dummy string variable
25
26          character*1, parameter :: TAB = char(9)                 !TAB wird das Steuerzeichen für den Tabulatorsprung zugewiesen
27  end module Global
28
29  ! Subroutine Modules
30  module qsort_c_module
31
32  ! Recursive Fortran 95 quicksort routine
33  ! sorts real numbers into ascending numerical order
34  ! Author: Juli Rew, SCD Consulting (juliana@ucar.edu), 9/03
35  ! Based on algorithm from Cormen et al., Introduction to Algorithms,
36  ! 1997 printing
37
38  ! Made F conformant by Walt Brainerd
39
40  implicit none
41  public :: QsortC
42  private :: Partition
43
44  contains
45
46  recursive subroutine QsortC(A, col, sortindex)
47          real, intent(in out), dimension(:,:) :: A
48          integer, intent(in) :: col
49          integer, intent(in out), dimension(:) :: sortindex
50          integer :: iq
51
52          if(size(A,2) > 1) then
53                  call Partition(A(:,:), col, sortindex, iq)
54                  call QsortC(A(:,:iq-1), col, sortindex(:iq-1))
55                  call QsortC(A(:,iq:), col, sortindex(iq:))
56          endif
57  end subroutine QsortC
58
59  subroutine Partition(A, col, sortindex, marker)
60          real, intent(in out), dimension(:,:) :: A
61          integer, intent(in) :: col
62          integer, intent(in out), dimension(:) :: sortindex
63          integer, intent(out) :: marker
64
65
66          integer :: i, j
67          integer :: tempint
68
69          real,dimension(size(A,1)) :: temp
70          real :: x      ! pivot point
71          x = A(col,1)
72          i= 0
73          j= size(A,2) + 1
74
75          do
76          j = j-1
77          do
78                  if (A(col,j) <= x) exit
79                  j = j-1
80          end do
81          i = i+1
82          do
83                  if (A(col,i) >= x) exit
84                  i = i+1
85          end do
86
87          if (i < j) then
88                  ! exchange A(i) and A(j)
89                  tempint = sortindex(i)
90                          sortindex(i) = sortindex(j)
91                          sortindex(j) = tempint
92
93                          temp = A(:,i)
94                  A(:,i) = A(:,j)
95                  A(:,j) = temp
96          elseif (i == j) then
97                  marker = i+1
98                  return
99          else
100                  marker = i
101                  return
102          endif
103          end do
104  end subroutine Partition
105
106  end module qsort_c_module
107
108
109          !files:
110          !#15 parameter file: feffsphere.par
111          !#25 input file: filein
112          !#35 output file: fileoutfeff
113          !#45 output file: fileoutcoo
114
115
116  !!!!!!!!!!!!!!!!!!!!!!
117  !MAIN part of program!
118  !!!!!!!!!!!!!!!!!!!!!!
119
120  program feffsphere
121  use Main
122  write(*,*) '****************************************'
123  write(*,*) 'feffsphere by A. Kompch version: ', VERSION
124  write(*,*) '****************************************'
125
126
127  call Read_par_file
128  call Read_atoms
129  !call Center2Origin
130  call Cutsphere
131  call Sort
132  call Write_FileOut
133  end program feffsphere
134
135
136  !!!!!!!!!!!!!
137  !SUBROUTINES!
138  !!!!!!!!!!!!!
139
140  subroutine Read_par_file
141          ! Read parameter file 'feffsphere.par' #15
142          use Global
143          implicit none
144
145          integer :: ntyp
146
147                  open(15,file='feffsphere.par', status='old', action= 'read', iostat=iostat)
148                          if (iostat == 0) then
149                                  read(15,'(a)',end=200,err=800), filein
150                                  read(15,'(a)',end=200,err=800), fileoutfeff
151                                  read(15,'(a)',end=200,err=800), fileoutcoo
152  !                               read(15,'(a)',end=200,err=800), fileoutxyz
153                                  read(15,'(a)',end=200,err=800), fileoutpdb
154                                  read(15,'(i6)',end=200,err=800), atno
155                                  read(15,*,end=200,err=800), dia
156                                  read(15,'(i2)'), ntyp
157                                  allocate (chartyp(ntyp))
158                                  do i=1,ntyp
159                                          read(15,'(a2)'), chartyp(i)
160                                  end do
161                          else
162                                  write(*,*) 'open parameter file <feffsphere.par> failed!'
163                          end if
164
165                  close (15)
166                  write(*,*) 'parameter file <feffsphere.par> succesfully read'
167                  return   !  successful exit
168                  200 continue
169                          print*,'Read_Input: FATAL: premature end-of-file in standard input'
170                          close (15)
171                          stop
172                  800 continue
173                          print*,'Read_Input: FATAL: read error in standard input'
174                          close (15)
175                          stop
176  end subroutine Read_par_file
177
178  subroutine Read_atoms
179          ! Read .coo file with atoms #25
180          use Global
181          implicit none
182
183          integer count1
184
185
186          open(25, file=filein, status='old', action= 'read', iostat=iostat)
187                  if(iostat == 0) then
188  !               write(*,*) 'Das Öffnen der Datei war ein voller Erfolg'
189                          i=0
190                  do
191                          read(25,'(a)', iostat=iostat) dummy
192                                  ! Bei EOF wird iostat /= 0
193                                  if (iostat /= 0) exit
194                                  i=i+1
195                          end do
196                  else
197                  write(*,*) 'Datei <', filein, '> konnte nicht geöffnet werden'
198                  end if
199          close(25)
200
201          tot=i
202          write(*,*) 'total number of atoms read: ', tot
203          allocate(pos(DIM,tot), newpos(DIM,tot), typ(tot), newtyp(tot), rpos(tot), stat=status)
204          if (status /= 0) then
205                  write(*,*) 'allocate failed!'
206                  stop
207          end if
208
209          open(25, file=filein, status='old', action= 'read', iostat=iostat)
210                  if(iostat == 0) then
211                          i=0
212                  do i=1, tot
213                          read(25,'(i6,1x,i2,5(1x,g13.6))', end=200, err=800) count1, typ(i), pos(:,i)
214                          end do
215                  else
216                  write(*,*) 'Datei <', filein, '> konnte nicht geöffnet werden'
217                  end if
218                  close(25)
219                  return   !  successful exit
220
221                  200 continue
222                          print*,'Read_atoms: FATAL: premature end-of-file in <',filein,'> at line: ', i
223                          close (25)
224                          stop
225                  800 continue
226                          print*,'Read_Input: FATAL: read error in <',filein,'> at line: ', i
227                          close (25)
228                          stop
229
230  end subroutine Read_atoms
231
232  subroutine Center2Origin
233          ! Find center of gravity and set to (0.0/0.0/0.0)
234          use Global
235          implicit none
236
237          real, dimension(DIM) :: mass_center
238
239          mass_center = sum(pos(:,:tot))/tot
240
241          do k=1,DIM
242                  pos(k,:tot) = pos(k,:tot) - mass_center(k)
243          end do
244  end subroutine Center2Origin
245
246  subroutine Cutsphere
247          use Global
248          implicit none
249
250          real :: rsq, r0isq
251          real, dimension(DIM) :: r0, ri, r0i
252
253
254          write(*,*), 'Cut sphere with diameter: ',dia,' around atom no. ',atno,'(',pos(1,atno),'/',pos(2,atno),'/',pos(3,atno), &
255                      'typ= ',typ(atno),') r= ',sqrt(dot_product(pos(:,atno),pos(:,atno)))
256
257          k=1
258          rsq=0.25*dia*dia                !r=1/4*dia^2
259          newpos(:,1) = pos(:,atno)
260          newtyp(1) = typ(atno)
261          r0 = pos(:,atno)
262
263          do i=1, tot
264                  ri = pos(:,i)
265                  r0i = r0 - ri
266                  r0isq = dot_product(r0i,r0i)
267                  if ((r0isq <= rsq) .and. (r0isq > 1.0)) then
268                          k=k+1
269                          newpos(:,k) = pos(:,i)
270                          newtyp(k) = typ(i)
271                  end if
272          end do
273
274          tot=k
275
276          !copy back to main pos(:,:) and typ(:) arrays
277          pos = newpos
278          typ = newtyp
279
280          !set positions and atom type to 0 for indexes larger than remaining (=inside diameter)
281          !number of atoms in pos(:,:) and typ(:)
282          pos(:,tot+1:) = 0.0
283          typ(tot+1:) = 0
284
285          !Move so that central atom is at origin
286                  do k=1,DIM
287                          pos(k,:tot) = pos(k,:tot) - pos(k,1)
288                  end do
289
290          return
291  end subroutine Cutsphere
292
293
294  subroutine Sort
295          use Global
296          use qsort_c_module
297          implicit none
298
299          real, dimension(:,:) :: table(4,tot)
300          integer, dimension(:) :: idx(tot)
301
302          real :: radsq, rad
303
304
305          write (*,*) 'in Sort: tot= ', tot
306          do i=1, tot
307                  idx(i) = i
308          end do
309
310          !set positions and atom type to 0 for indexes larger than remaining (=inside diameter)
311          !number of atoms in pos(:,:) and typ(:)
312          pos(:,tot+1:) = 0.0
313          typ(tot+1:) = 0
314          newpos = 0.0
315          newtyp = 0
316
317          !make new table(:,:) array with positions and radial distance from center atom
318          table(:3,:tot)=pos(:,:tot)
319          do i=1, tot
320                  radsq=dot_product(pos(:,i),pos(:,i))
321                  rad=sqrt(radsq)
322                  table(4,i)=rad
323          end do
324
325          call QsortC(table, 4, idx)
326          pos=table(:3,:)
327          do i=1,tot
328                  newtyp(i)=typ(idx(i))
329          end do
330          typ=newtyp
331          rpos=table(4,:)
332          return
333
334  end subroutine Sort
335
336  subroutine Write_FileOut
337          use Global
338          implicit none
339
340          open(35, file=fileoutfeff, status='replace', action= 'write', iostat=iostat)
341                  if(iostat == 0) then
342                          i=1
343                          write(35,'(a)') 'ATOMS'
344                          write(35, '(1x,3(f9.5,3x),i2,3x,a13,3x,f8.5)', err=800), pos(:,i), 0, chartyp(typ(i)), rpos(i)
345                          do i=2, tot
346                                  write(35, '(3(f13.5),i4,a4,f13.5)', err=800), pos(:,i), typ(i), chartyp(typ(i)), rpos(i)
347                          end do
348                  end if
349          close(35)
350          open(45, file=fileoutcoo, status='replace', action= 'write', iostat=iostat)
351                  if(iostat == 0) then
352                          do i=1, tot
353                                  write(45, '(i6,1x,i2,5(1x,g13.6))', err=850), i, typ(i), pos(:,i), 0.0, 1.0
354                          end do
355                  end if
356          close(45)
357  !       open(55, file=fileoutxyz, status='replace', action= 'write', iostat=iostat)
358  !               if(iostat == 0) then
359  !                       write(55,'(i6)'), tot
360  !                       write(55,*)
361  !               do i=1,tot
362  !                       write(55,'(a2,3(1x,g13.6))', err=875) chartyp(typ(i)), pos(:,i)
363  !                       end do
364  !               end if
365  !       close(55)
366          open(65, file=fileoutpdb, status='replace', action= 'write', iostat=iostat)
367                  if(iostat == 0) then
368                          do i=1, tot
369                                  write(65,'(a6,i5,1x,a2,1x,1x,a1,a3,1x,a1,i4,a1,3x,3f8.3,2f6.2,11x,a2,a2)')'ATOM  ',i,chartyp(typ(i)),' ','UNK',' ',0,' ', &
370                                  pos(:,i),1.,0.0,chartyp(typ(i))
371                          end do
372                  end if
373          close(65)
374
375
376          return
377          800 continue
378                  write(*,*),'Write_FileOut: FATAL: write error in <',fileoutfeff,'> at line: ', i
379                  close(35)
380                  stop
381          850 continue
382                  write(*,*),'Write_FileOut: FATAL: write error in <',fileoutcoo,'> at line: ', i
383                  close(45)
384                  stop
385  !       875 continue
386  !               write(*,*),'Write_FileOut: FATAL: write error in <',fileoutxyz,'> at line: ', i
387  !               close(55)
388  !               stop
389  !       9301  format(a6,i5,a4,1x,a1,a3,1x,a1,i4,a1,3x,3f8.3,2f6.2,1x,i3)
390
391  end subroutine Write_FileOut

