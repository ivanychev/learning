%% This bibstyle attempts to format bibliography according to
%% GOST 7.0.5-2008 for bibliographic reference.
%% Possible entries are article, book, inproceedings, incollection, conference, 
%% techreport, online, phdthesis and misc.

ENTRY
  { address
    annote
    author
    booktitle
    bookauthor
    chapter
    edition
    editor
    compiler
    howpublished
    institution
    journal
    key
    month
    note
    number
    organization
    pages
    publisher
    school
    series
    title
    type
    volume
    year
    language
    booklanguage
    numpages
    url
    urldate
    isbn
    doi
    eprinttype   % = archivePrefix
    eprintclass  % = primaryClass
    eprint
  }
  {}
  { label }

INTEGERS { output.state before.all mid.sentence after.sentence after.block after.dblslash after.slash after.column after.semicolumn }

FUNCTION {init.state.consts}
{ #0 'before.all :=
  #1 'mid.sentence :=
  #2 'after.sentence :=
  #3 'after.block :=
  #4 'after.dblslash :=
  #5 'after.slash :=
  #6 'after.column :=
  #7 'after.semicolumn :=
}

STRINGS { s t }

STRINGS { curlanguage }

FUNCTION {change.language}
{ booklanguage empty$
    { "" }
    { booklanguage  'curlanguage :=
      "\selectlanguageifdefined{"
      curlanguage *
      "}" *
    }
  if$
}

FUNCTION {output.nonnull}
{
  swap$
  output.state mid.sentence =
    { ", " * write$ }
    { output.state after.block =
        { add.period$ write$
          "~--- " write$
        }
        { output.state before.all =
            'write$
            { output.state after.dblslash =
                { "~//" * change.language * " " * write$ }
                { output.state after.slash =
                    { "~/ " * write$ }
                    { output.state after.column =
                        { ": " * write$ }
                        { output.state after.semicolumn =
                            { "; " * write$ }
                        { add.period$ " " * write$ }
                       if$
                        }
                      if$
                    }
                  if$
                }
              if$
            }
          if$
        }
      if$
      mid.sentence 'output.state :=
    }
  if$
  newline$
}

FUNCTION {output}
{ duplicate$ empty$
    'pop$
    'output.nonnull
  if$
}

FUNCTION {output.check}
{ 't :=
  duplicate$ empty$
    { pop$ "empty " t * " in " * cite$ * warning$ }
    'output.nonnull
  if$
}

FUNCTION {fin.entry}
{ add.period$
  write$
  newline$
}

FUNCTION {new.block}
{ output.state before.all =
    'skip$
    { after.block 'output.state := }
  if$
}

FUNCTION {new.dblslash}
{ output.state before.all =
    'skip$
    { after.dblslash 'output.state := }
  if$
}

FUNCTION {new.slash}
{ output.state before.all =
    'skip$
    { after.slash 'output.state := }
  if$
}

FUNCTION {new.column}
{ output.state before.all =
    'skip$
    { after.column 'output.state := }
  if$
}

FUNCTION {new.semicolumn}
{ output.state before.all =
    'skip$
    { after.semicolumn 'output.state := }
  if$
}

FUNCTION {new.sentence}
{ output.state after.block =
    'skip$
    { output.state before.all =
        'skip$
        { after.sentence 'output.state := }
      if$
    }
  if$
}

FUNCTION {add.blank}
{ " " * before.all 'output.state :=
}

FUNCTION {not}
{   { #0 }
    { #1 }
  if$
}

FUNCTION {and}
{   'skip$
    { pop$ #0 }
  if$
}

FUNCTION {or}
{   { pop$ #1 }
    'skip$
  if$
}

INTEGERS { len }

FUNCTION {field.or.null}
{ duplicate$ empty$
    { pop$ "" }
    'skip$
  if$
}

FUNCTION {emphasize}
{ duplicate$ empty$
    { pop$ "" }
    { "\emph{" swap$ * "}" * }
  if$
}

FUNCTION {bracify}
{ duplicate$ empty$
    { pop$ "{}" }
    { "{" swap$ * "}" * }
  if$
}

FUNCTION {space.word}
{ " " swap$ * " " * }

FUNCTION {bbl.edby}    %  { "\bbledby{}" }
{ curlanguage "english" =
   {"Eds."}
   { curlanguage "ukrainian" =
      {"{\cyr\CYRP\cyrii\cyrd\ \cyrr\cyre\cyrd.}"}
      { curlanguage "russian" =
         {"{\cyr\CYRP\cyro\cyrd\ \cyrr\cyre\cyrd.}"}
         { curlanguage "german" =
            { "Eds." }
            {"language is not defined: " language "edby" * * warning$ "Eds."}
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.cmplr}
{ curlanguage "english" =
   { "Compiler"}
   { curlanguage "german" =
      { "Hrsg." }
      { curlanguage "ukrainian" =
         {"{\cyr\CYRU\cyrk\cyrl.}"}
         { curlanguage "russian" =
            {"{\cyr\CYRS\cyro\cyrs\cyrt.}"}
            {"language is not defined: " language  "cmplr" * * warning$ "Compiler"}
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.edition} %  { "\bbledition{}" }
{ curlanguage "english" =
   {"ed."}
   { curlanguage "ukrainian" =
      {"{\cyr\cyrv\cyri\cyrd.}"}
      { curlanguage "russian" =
         {"{\cyr\cyri\cyrz\cyrd.}"}
         { curlanguage "german" =
            {" {aus.}" } %%%% { "Aufl." } ??
            { curlanguage "italian" =
               {"edizione"}
               { curlanguage "french" =
                  {"\'{e}dition"}
                  {"language is not defined: " language  "edition" * * warning$ "edition"}
               if$}
            if$}
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.vvol}    %  { "\bblVol{}" }
{ curlanguage "english" = curlanguage "french" = or curlanguage "italian" = or
   {"Vol."}
   { curlanguage "ukrainian" = curlanguage "russian" = or
      {"\CYRT."}
      { curlanguage "german" =
         {"{Bd.}"} %%%% { "Vol." }
         {"language is not defined: " language  "vvol" * * warning$ "Vol."}
      if$}
   if$}
if$}

FUNCTION {bbl.of}      %  { "\bblof{}" }
{ curlanguage "english" =
   {"of"}
   { curlanguage "german" =
      { "von" }
      { curlanguage "ukrainian" =
         { "{\cyr\cyrii\cyrz}" }
         { curlanguage "russian" =
            { "{\cyr\cyri\cyrz}" }
            {"language is not defined: " language "of" * * warning$ "of"}
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.etal}      %  { "\bblof{}" }
{ curlanguage "english" =
   {"et~al."}
   { curlanguage "german" =
      { "u.~a." }
      { curlanguage "ukrainian" =
         {"{\cyr\cyrt\cyra~\cyrii\cyrn.}"}
         { curlanguage "russian" =
            {"{\cyr\cyri~\cyrd\cyrr.}"}
            {"language is not defined: " language  "et~al" * * warning$ "et~al."}
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.nr}     %   { "\bblno{}" }
{ curlanguage "english" =
   {"No."}
   { curlanguage "italian" =
      { "No" }
      { curlanguage "ukrainian" = curlanguage "russian" = or
         { "{\cyr\textnumero}" }
         { curlanguage "german" =
            {"{H.}"} %%% { "an." }
            {"language is not defined: " language "nr" * * warning$ "no."}
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.pages}    % { "\bblpp." }
{ curlanguage "english" = curlanguage "french" = or curlanguage "italian" = or
   {"p."} %%% {"pp."}
   { curlanguage "ukrainian" = curlanguage "russian" = or
      {"{\cyr\cyrs.}"}
      { curlanguage "german" =
         {"S."} %%%% { "s." }
         {"language is not defined: " language  "pages" * * warning$ "p."}
      if$}
   if$}
if$}

FUNCTION {bbl.page}   %   { "\bblp."
{ curlanguage "english" = curlanguage "french" = or curlanguage "italian" = or
   {"p."}
   { curlanguage "ukrainian" = curlanguage "russian" = or
      {"{\cyr\cyrs.}"}
      { curlanguage "german" =
         {"S."} %%%% { "s." }
         {"language is not defined: " language  "page" * * warning$ "p."}
      if$}
   if$}
if$}

FUNCTION {bbl.ppages}%    { "\bblPp." }
{ curlanguage "english" = curlanguage "french" = or curlanguage "italian" = or
   {"P."} %%%% { "Pp." }
   { curlanguage "ukrainian" = curlanguage "russian" = or
      {"{\cyr\CYRS.}"}
      { curlanguage "german" =
         {"S."}
         {"language is not defined: " language "ppages" * * warning$ "P."}
      if$}
   if$}
if$}

FUNCTION {bbl.ppage}  %   { "\bblP." }
{ curlanguage "english" = curlanguage "french" = or curlanguage "italian" = or
   {"P."}
   { curlanguage "ukrainian" = curlanguage "russian" = or
      {"{\cyr\CYRS.}"}
      { curlanguage "german" =
         {"S."}
         {"language is not defined: " language  "ppage" * * warning$ "P."}
      if$}
   if$}
if$}

FUNCTION {bbl.urldate}
{ curlanguage "english" =
   {"accessed"}
   { curlanguage "ukrainian" =
      { "{\cyrd\cyra\cyrt\cyra\ \cyrz\cyrv\cyre\cyrr\cyrn\cyre\cyrn\cyrn\cyrya}" }
      { curlanguage "russian" =
         { "{\cyrd\cyra\cyrt\cyra\ \cyro\cyrb\cyrr\cyra\cyrshch\cyre\cyrn\cyri\cyrya}" }
         { curlanguage "german" =
            { "{online; abgerufen}" }
            { "language is not defined: " language "urldate" * * warning$ "online; accessed" }
         if$}
      if$}
   if$}
if$}

FUNCTION {bbl.techreport} % rename to bbl.techreport
{ curlanguage "english" =
   { "Report" }
   { curlanguage "german" =
      { "Bericht" }
      { curlanguage "russian" =
         { "{\cyr\CYRO\cyrt\cyrch\cyre\cyrt}" }
         { "language is not defined: " language "techrep" * * warning$ "Rep." }
      if$}
   if$}
if$}

FUNCTION {bbl.phdthesis}
{ curlanguage "english" =
   { "Ph.\,D. Thesis" }
   { curlanguage "german" =
      { "Diss.~Ph.\,D." }
      { curlanguage "russian" =
         { "{\cyr\CYRD\cyri\cyrs\cyrs\ldots\ \cyrk\cyra\cyrn\cyrd\cyri"
           "\cyrd\cyra\cyrt\cyra\ \cyrn\cyra\cyru\cyrk}" * }
         { curlanguage "french" =
           { "Th\`{e}se de doctorat" }
           { "language is not defined: " language "phdthesis" * * warning$ "Ph.\,D. thesis" }
         if$}
      if$}
   if$}
if$}

INTEGERS { nameptr namesleft numnames }

FUNCTION {format.names}
{
  's :=
  #1 'nameptr :=
  s num.names$ 'numnames :=
  numnames 'namesleft :=
    { namesleft #0 > }
    { s nameptr
      "{vv~}{ll}{~jj}{~f.}" format.name$ 't :=
      nameptr #1 >
        { nameptr #6 =
          numnames #6 > and
            { "others" 't :=
              #1 'namesleft := }
            'skip$
          if$
          namesleft #1 >
            { ", " * t * }
            { t "others" =
          t "~others" =
          or
                { " " * bbl.etal * }
                { ", " * t * }
              if$
            }
          if$
        }
        't
      if$
      nameptr #1 + 'nameptr :=
      namesleft #1 - 'namesleft :=
    }
  while$
}

STRINGS  { bibinfo}

FUNCTION {bibinfo.check}
{ swap$
  duplicate$ missing$
    {
      pop$ pop$
      ""
    }
    { duplicate$ empty$
        {
          swap$ pop$
        }
        { swap$
          swap$ *
        }
      if$
    }
  if$
}

FUNCTION {format.names.ed} 
{
  's :=
  "" 't :=
  #1 'nameptr :=
  s num.names$ 'numnames :=
  numnames 'namesleft :=
    { namesleft #0 > }
    { s nameptr
      "{f.~}{vv~}{ll}{, jj}"
      format.name$
      bibinfo bibinfo.check
      't :=
      nameptr #1 >
        {
          namesleft #1 >
            { ", " * t * }
            {
              s nameptr "{ll}" format.name$ duplicate$ "others" =
                { 't := }
                { pop$ }
              if$
              numnames #2 >
                { "," * }
                'skip$
              if$
              t "others" =
                {
                  " " * bbl.etal *
                }
                {
                  space.word t *
                }
              if$
            }
          if$
        }
        't
      if$
      nameptr #1 + 'nameptr :=
      namesleft #1 - 'namesleft :=
    }
  while$
}

FUNCTION {format.names.rev}
{
  's :=
  #1 'nameptr :=
  s num.names$ 'numnames :=
  numnames 'namesleft :=
    { namesleft #0 > }
    { s nameptr
      %"{f.}{~vv}{~ll}{, jj}" format.name$ 't :=
      "{ff}{~vv}{~ll}{, jj}" format.name$ 't :=
      nameptr #1 >
        { nameptr #4 =
          numnames #4 > and
            { "others" 't :=
              #1 'namesleft := }
            'skip$
          if$
          namesleft #1 >
            { ", " * t * }
            { t "others" =
          t "~others" =
          or
                { " " * bbl.etal * }
                { ", " * t * }
              if$
            }
          if$
        }
        't
      if$
      nameptr #1 + 'nameptr :=
      namesleft #1 - 'namesleft :=
    }
  while$
}

FUNCTION {format.authors}
{ author empty$
    { "" }
    { author format.names emphasize}
  if$
}

FUNCTION {format.editors.after}
{ editor empty$
    { "" }
    { bbl.edby "\" * editor format.names.ed * }
  if$
}

FUNCTION {format.compiler.after}
{ compiler empty$
    { "" }
    { bbl.cmplr "\ " * compiler format.names.rev * }
  if$
}

FUNCTION {format.title}
{ title empty$
    { "" }
    { title "t" change.case$ }
  if$
}

FUNCTION {format.date}
{ year empty$
    { month empty$
        { "" }
        { "there's a month but no year in " cite$ * warning$
          month
        }
      if$
    }
    { year }
  if$
}



FUNCTION {output.address.institution.organization.school}
{
  address empty$
    'skip$
    { address output
      institution empty$
        { organization empty$
            {
              school empty$
              'skip$
              { new.column }
              if$
            }
            { new.column }
          if$
        }
        { new.column }
      if$
    }
  if$
  institution empty$
    { organization empty$
        { school output }
        { organization output }
      if$  
      }
    { institution output }
  if$
}

FUNCTION {output.address.publisher}
{
  address empty$
    'skip$
    { 
      publisher empty$
        { output.address.institution.organization.school }
        { 
          address output 
          new.column 
          publisher output }
      if$
    }
  if$
}

FUNCTION {output.bibitem}
{ newline$
  "\bibitem" write$
  cite$ bracify write$
  newline$
  language empty$
    { "english" 'curlanguage := }
    { language  'curlanguage := }
  if$
  "\selectlanguageifdefined" curlanguage bracify * write$
  ""
  before.all 'output.state :=
}

FUNCTION {n.dashify}
{ 't :=
  ""
    { t empty$ not }
    { t #1 #1 substring$ "-" =
        { t #1 #2 substring$ "--" = not
            { "--" *
              t #2 global.max$ substring$ 't :=
            }
            {   { t #1 #1 substring$ "-" = }
                { "-" *
                  t #2 global.max$ substring$ 't :=
                }
              while$
            }
          if$
        }
        { t #1 #1 substring$ *
          t #2 global.max$ substring$ 't :=
        }
      if$
    }
  while$
}

FUNCTION {format.btitle}
{ title
}

FUNCTION {tie.or.space.connect}
{ duplicate$ text.length$ #3 <
    { "~" }
    { " " }
  if$
  swap$ * *
}

FUNCTION {tie.connect}
 {"~"
  swap$ * *
 }

FUNCTION {either.or.check}
{ empty$
    'pop$
    { "can't use both " swap$ * " fields in " * cite$ * warning$ }
  if$
}

FUNCTION {format.bvolume}
{ volume empty$
    { "" }
    { bbl.vvol volume tie.connect }
  if$
}

FUNCTION {format.number.series}
{ volume empty$
    { number empty$
        { series field.or.null }
        { series empty$
            { "there's a number but no series in " cite$ * warning$
              bbl.nr }
            {
              new.sentence
              series
              bbl.nr
              tie.or.space.connect }
          if$
          number tie.or.space.connect
        }
      if$
    }
    { "" }
  if$
}

FUNCTION {bbl.first}
{ "1st" }

FUNCTION {bbl.second}
{ "2nd" }

FUNCTION {bbl.third}
{ "3rd" }

FUNCTION {bbl.fourth}
{ "4th" }

FUNCTION {bbl.fifth}
{ "5th" }

FUNCTION {bbl.st}
{ "st" }

FUNCTION {bbl.nd}
{ "nd" }

FUNCTION {bbl.rd}
{ "rd" }

FUNCTION {bbl.th}
{ "th" }

FUNCTION {eng.ord}
{ duplicate$ "1" swap$ *
  #-2 #1 substring$ "1" =
     { bbl.th * }
     { duplicate$ #-1 #1 substring$
       duplicate$ "1" =
         { pop$ bbl.st * }
         { duplicate$ "2" =
             { pop$ bbl.nd * }
             { "3" =
                 { bbl.rd * }
                 { bbl.th * }
               if$
             }
           if$
          }
       if$
     }
   if$
}

FUNCTION {is.num}
{ chr.to.int$
  duplicate$ "0" chr.to.int$ < not
  swap$ "9" chr.to.int$ > not and
}

FUNCTION {extract.num}
{ duplicate$ 't :=
  "" 's :=
  { t empty$ not }
  { t #1 #1 substring$
    t #2 global.max$ substring$ 't :=
    duplicate$ is.num
      { s swap$ * 's := }
      { pop$ "" 't := }
    if$
  }
  while$
  s empty$
    'skip$
    { pop$ s }
  if$
}

FUNCTION {convert.edition}
{ extract.num "l" change.case$ 's :=
  curlanguage "english" =
  { 
    s "first" = s "1" = or
    { bbl.first 't := }
    { s "second" = s "2" = or
      { bbl.second 't := }
      { s "third" = s "3" = or
        { bbl.third 't := }
        { s "fourth" = s "4" = or
          { bbl.fourth 't := }
          { s "fifth" = s "5" = or
            { bbl.fifth 't := }
            { s #1 #1 substring$ is.num
              { s eng.ord 't := }
              { edition 't := }
              if$
            }
            if$
          }
          if$
        }
        if$
      }
      if$
    }
    if$
  }
  { s #1 #1 substring$ is.num
    { s "-\cyre" * 't := }
    { edition 't := }
    if$
  }
  if$  
  t
}

FUNCTION {format.edition}
{ edition duplicate$ empty$ 'skip$ 
    { convert.edition
      output.state mid.sentence =
        { "l" }
        { "t" }
      if$ change.case$
      "~" * bbl.edition *
    }
  if$
}

INTEGERS { multiresult }

FUNCTION {multi.page.check}
{ 't :=
  #0 'multiresult :=
    { multiresult not
      t empty$ not
      and
    }
    { t #1 #1 substring$
      duplicate$ "-" =
      swap$ duplicate$ "," =
      swap$ "+" =
      or or
        { #1 'multiresult := }
        { t #2 global.max$ substring$ 't := }
      if$
    }
  while$
  multiresult
}

FUNCTION {format.pages}
{ pages empty$
    { "" }
    { pages multi.page.check
        { bbl.ppages pages n.dashify tie.connect }
        { bbl.ppage pages tie.connect }
      if$
    }
  if$
}

FUNCTION {format.pages.page}
{ pages empty$
    { numpages empty$
      { "" }
      { numpages bbl.pages tie.connect }
    if$
    }
    { format.pages }
  if$
}

FUNCTION {format.volume}
{ volume empty$
    { "" }
    { bbl.vvol volume tie.or.space.connect }
  if$
}

FUNCTION {format.number}
{ number empty$
    { "" }
    { bbl.nr number tie.or.space.connect }
  if$
}

FUNCTION {format.thesis.type}
{ type empty$
    'skip$
    { pop$
      type "t" change.case$
    }
  if$
}

FUNCTION {author.before}
{
  author empty$
    'skip$
    { format.authors output
      new.sentence
    }
  if$
}

FUNCTION {editor.after}
{
  editor empty$
    {}
    { 
      format.editors.after  output
      new.column
    }
  if$
}

FUNCTION {format.url}
{ url empty$
    { "" }
    {
      "URL: \url{" url * "}" *
    }
  if$
}

FUNCTION {format.doi}
{ doi empty$
    { "" }
    {
      "doi: " doi * "" *
    }
  if$
}

FUNCTION {format.number.report}
{ number empty$
    { "" }
    { bbl.techreport " " * number * "" *}
  if$
}

FUNCTION {output.url}
{
  format.url output
}

FUNCTION {article}
{
  output.bibitem
  author.before
  format.title "title" output.check
  new.dblslash
  journal "journal" output.check
  mid.sentence 'output.state :=
  format.date "year" output.check
  new.sentence
  format.volume output
  new.sentence 
  format.number output 
  new.sentence
  format.pages.page output
  new.sentence
  format.doi output
  new.sentence
  output.url
  new.sentence
  note output
  new.sentence
  fin.entry
}

FUNCTION {book}
{
  output.bibitem
  author.before
  format.btitle "title" output.check
  new.slash
  editor.after
  new.block
  format.edition output
  new.block
  output.address.publisher
  format.date "year" output.check
  new.sentence
  format.bvolume output
  new.sentence
  format.pages.page output
  new.sentence
  note output
  new.sentence
  output.url
  fin.entry
}

FUNCTION {inproceedings}
{ output.bibitem
  author.before
  new.sentence
  format.title "title" output.check
  new.dblslash
  booktitle "booktitle" output.check
  new.slash
  editor.after
  new.block
  output.address.publisher
  format.date "year" output.check
  new.sentence
  format.bvolume output
  new.sentence
  format.pages.page output
  new.sentence
  note output
  new.sentence
  output.url
  fin.entry
}

FUNCTION {conference} { inproceedings }
FUNCTION {incollection} { inproceedings }


FUNCTION {techreport}
{
  output.bibitem
  format.authors emphasize output
  new.sentence
  format.title "title" output.check
  new.sentence
  output.address.institution.organization.school
  format.date "year" output.check
  new.sentence
  format.number.report output 
  new.sentence
  note output
  new.sentence
  fin.entry
}

FUNCTION {online}
{ output.bibitem
  format.authors output
  new.sentence
  format.title output
  new.sentence
  address empty$
    { new.sentence }
    { new.block }
  if$
  output.address.publisher
  format.date "year" output.check
  new.sentence
  output.url
  new.sentence
  note output
  fin.entry
}

FUNCTION {phdthesis}
{ output.bibitem
  format.authors "author" output.check
  new.sentence
  format.btitle "title" output.check
  new.sentence
  output.address.institution.organization.school
  format.date "year" output.check
  new.sentence
  bbl.phdthesis format.thesis.type output.nonnull
  new.sentence
  format.pages.page output
  new.sentence
  note output
  new.sentence
  output.url
  fin.entry
}

FUNCTION {misc}
{ output.bibitem
  format.authors output
  new.sentence
  format.title output
  new.block
  output.address.publisher
  format.date "year" output.check
  new.sentence
  format.pages.page output
  new.sentence
  output.url
  new.sentence
  note output
  fin.entry
}

FUNCTION {default.type} { misc }

MACRO {jan} {"\bbljan{}"}
MACRO {feb} {"\bblfeb{}"}
MACRO {mar} {"\bblmar{}"}
MACRO {apr} {"\bblapr{}"}
MACRO {may} {"\bblmay{}"}
MACRO {jun} {"\bbljun{}"}
MACRO {jul} {"\bbljul{}"}
MACRO {aug} {"\bblaug{}"}
MACRO {sep} {"\bblsep{}"}
MACRO {oct} {"\bbloct{}"}
MACRO {nov} {"\bblnov{}"}
MACRO {dec} {"\bbldec{}"}


MACRO {aa}{"Astron. \& Astrophys."}
MACRO {aasup}{"Astron. \& Astrophys. Suppl. Ser."}
MACRO {aj} {"Astron. J."}
MACRO {aph} {"Acta Phys."}
MACRO {advp} {"Adv. Phys."}
MACRO {ajp} {"Amer. J. Phys."}
MACRO {ajm} {"Amer. J. Math."}
MACRO {amsci} {"Amer. Sci."}
MACRO {anofd} {"Ann. Fluid Dyn."}
MACRO {am} {"Ann. Math."}
MACRO {ap} {"Ann. Phys. (NY)"}
MACRO {adp} {"Ann. Phys. (Leipzig)"}
MACRO {ao} {"Appl. Opt."}
MACRO {apl} {"Appl. Phys. Lett."}
MACRO {app} {"Astroparticle Phys."}
MACRO {apj} {"Astrophys. J."}
MACRO {apjsup} {"Astrophys. J. Suppl."}
MACRO {apss} {"Astrophys. Space Sci."}
MACRO {araa} {"Ann. Rev. Astron. Astrophys."}
MACRO {baas} {"Bull. Amer. Astron. Soc."}
MACRO {baps} {"Bull. Amer. Phys. Soc."}
MACRO {cmp} {"Comm. Math. Phys."}
MACRO {cpam} {"Commun. Pure Appl. Math."}
MACRO {cppcf} {"Comm. Plasma Phys. \& Controlled Fusion"}
MACRO {cpc} {"Comp. Phys. Comm."}
MACRO {cqg} {"Class. Quant. Grav."}
MACRO {cra} {"C. R. Acad. Sci. A"}
MACRO {fed} {"Fusion Eng. \& Design"}
MACRO {ft} {"Fusion Tech."}
MACRO {grg} {"Gen. Relativ. Gravit."}
MACRO {ieeens} {"IEEE Trans. Nucl. Sci."}
MACRO {ieeeps} {"IEEE Trans. Plasma Sci."}
MACRO {ijimw} {"Interntl. J. Infrared \& Millimeter Waves"}
MACRO {ip} {"Infrared Phys."}
MACRO {irp} {"Infrared Phys."}
MACRO {jap} {"J. Appl. Phys."}
MACRO {jasa} {"J. Acoust. Soc. America"}
MACRO {jcp} {"J. Comp. Phys."}
MACRO {jchp} {"J. Chem. Phys."}
MACRO {jetp} {"Sov. Phys.--JETP"}
MACRO {jfe} {"J. Fusion Energy"}
MACRO {jfm} {"J. Fluid Mech."}
MACRO {jmp} {"J. Math. Phys."}
MACRO {jne} {"J. Nucl. Energy"}
MACRO {jnec} {"J. Nucl. Energy, C: Plasma Phys., Accelerators, Thermonucl. Res."}
MACRO {jnm} {"J. Nucl. Mat."}
MACRO {jpc} {"J. Phys. Chem."}
MACRO {jpp} {"J. Plasma Phys."}
MACRO {jpsj} {"J. Phys. Soc. Japan"}
MACRO {jsi} {"J. Sci. Instrum."}
MACRO {jvst} {"J. Vac. Sci. \& Tech."}
MACRO {nat} {"Nature"}
MACRO {nature} {"Nature"}
MACRO {nedf} {"Nucl. Eng. \& Design/Fusion"}
MACRO {nf} {"Nucl. Fusion"}
MACRO {nim} {"Nucl. Inst. \& Meth."}
MACRO {nimpr} {"Nucl. Inst. \& Meth. in Phys. Res."}
MACRO {np} {"Nucl. Phys."}
MACRO {npb} {"Nucl. Phys. B"}
MACRO {nt/f} {"Nucl. Tech./Fusion"}
MACRO {npbpc} {"Nucl. Phys. B (Proc. Suppl.)"}
MACRO {inc} {"Nuovo Cimento"}
MACRO {nc} {"Nuovo Cimento"}
MACRO {pf} {"Phys. Fluids"}
MACRO {pfa} {"Phys. Fluids A: Fluid Dyn."}
MACRO {pfb} {"Phys. Fluids B: Plasma Phys."}
MACRO {pl} {"Phys. Lett."}
MACRO {pla} {"Phys. Lett. A"}
MACRO {plb} {"Phys. Lett. B"}
MACRO {prep} {"Phys. Rep."}
MACRO {pnas} {"Proc. Nat. Acad. Sci. USA"}
MACRO {pp} {"Phys. Plasmas"}
MACRO {ppcf} {"Plasma Phys. \& Controlled Fusion"}
MACRO {phitrsl} {"Philos. Trans. Roy. Soc. London"}
MACRO {prl} {"Phys. Rev. Lett."}
MACRO {pr} {"Phys. Rev."}
MACRO {physrev} {"Phys. Rev."}
MACRO {pra} {"Phys. Rev. A"}
MACRO {prb} {"Phys. Rev. B"}
MACRO {prc} {"Phys. Rev. C"}
MACRO {prd} {"Phys. Rev. D"}
MACRO {pre} {"Phys. Rev. E"}
MACRO {ps} {"Phys. Scripta"}
MACRO {procrsl} {"Proc. Roy. Soc. London"}
MACRO {rmp} {"Rev. Mod. Phys."}
MACRO {rsi} {"Rev. Sci. Inst."}
MACRO {science} {"Science"}
MACRO {sciam} {"Sci. Am."}
MACRO {sam} {"Stud. Appl. Math."}
MACRO {sjpp} {"Sov. J. Plasma Phys."}
MACRO {spd} {"Sov. Phys.--Doklady"}
MACRO {sptp} {"Sov. Phys.--Tech. Phys."}
MACRO {spu} {"Sov. Phys.--Uspekhi"}
MACRO {st} {"Sky and Telesc."}

MACRO {appopt} {"Appl. Opt."}
MACRO {bell}   {"Bell Syst. Tech. J."}
MACRO {ell}    {"Electron. Lett."}
MACRO {jasp}   {"J. Appl. Spectr."}
MACRO {jqe}    {"IEEE J. Quantum Electron."}
MACRO {jlwt}   {"J. Lightwave Technol."}
MACRO {jmo}    {"J. Mod. Opt."}
MACRO {josa}   {"J. Opt. Soc. America"}
MACRO {josaa}  {"J. Opt. Soc. Amer.~A"}
MACRO {josab}  {"J. Opt. Soc. Amer.~B"}
MACRO {jdp}    {"J. Phys. (Paris)"}
MACRO {oc}     {"Opt. Commun."}
MACRO {ol}     {"Opt. Lett."}
MACRO {os}     {"Opt. Spectrosc."}
MACRO {phtl}   {"IEEE Photon. Technol. Lett."}
MACRO {pspie}  {"Proc. Soc. Photo-Opt. Instrum. Eng."}
MACRO {sjot}   {"Sov. J. Opt. Technol."}
MACRO {sjqe}   {"Sov. J. Quantum Electron."}
MACRO {sleb}   {"Sov. Phys.--Leb. Inst. Rep."}
MACRO {stph}   {"Sov. Phys.--Techn. Phys."}
MACRO {stphl}  {"Sov. Techn. Phys. Lett."}
MACRO {vr}     {"Vision Res."}
MACRO {zph}    {"Z. f. Physik"}
MACRO {zphb}   {"Z. f. Physik~B"}
MACRO {zphd}   {"Z. f. Physik~D"}
MACRO {sse} {"Solid-State Electron."}
MACRO {pss} {"Phys. Sol. State"}
MACRO {sst} {"Semicond. Sci. Tech."}
MACRO {nl}  {"Nano Lett."}

READ

STRINGS { longest.label }

INTEGERS { number.label longest.label.width }

FUNCTION {initialize.longest.label}
{ "" 'longest.label :=
  #1 'number.label :=
  #0 'longest.label.width :=
}

EXECUTE {initialize.longest.label}

FUNCTION {forward.pass}
{ number.label int.to.str$ 'label :=
  number.label #1 + 'number.label :=
  label width$ longest.label.width >
    { label 'longest.label :=
      label width$ 'longest.label.width :=
    }
    'skip$
  if$
}

ITERATE {forward.pass}

FUNCTION {begin.bib}
{ "\begin{thebibliography}{"  longest.label  * "}" * write$ newline$
  "\def\selectlanguageifdefined#1{"                  write$ newline$
  "\expandafter\ifx\csname date#1\endcsname\relax"   write$ newline$
  "\else\selectlanguage{#1}\fi}"                     write$ newline$
  preamble$ empty$
    'skip$
    { preamble$ write$ newline$ }
  if$
}

EXECUTE {begin.bib}

EXECUTE {init.state.consts}

ITERATE {call.type$}

FUNCTION {end.bib}
{ newline$
  "\end{thebibliography}" write$ newline$
}

EXECUTE {end.bib}
