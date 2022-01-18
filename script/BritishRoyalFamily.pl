/****Sex is male****/
male(p_Phillip).
male(p_Charles).
male(c_m_Phillips).
male(t_Laurence).
male(p_Andrew).
male(p_Edward).
male(p_William).
male(p_Harry).
male(peter_Phillips).
male(m_Tindall).
male(j_v_Severn).
male(p_George).
male(m_g_Tindall).

/****Sex is female****/
female(q_ElizabethII).
female(p_Diana).
female(c_p_Bowles).
female(p_Anne).
female(s_Ferguson).
female(s_r_Jones).
female(k_Middleton).
female(a_Kelly).
female(z_Phillips).
female(p_Beatrice).
female(p_Eugenie).
female(l_l_m_Windsor).
female(p_Charlotte).
female(s_Phillips).
female(i_Phillips).

/****Parent Relationship****/

/****1st Generaton****/

parent(q_ElizabethII,p_Charles).
parent(p_Phillip,p_Charles).
parent(q_ElizabethII,p_Anne).
parent(p_Phillip,p_Anne).
parent(q_ElizabethII,p_Andrew).
parent(p_Phillip,p_Andrew).
parent(q_ElizabethII,p_Edward).
parent(p_Phillip,p_Edward).

/****2nd Generation****/

parent(p_Diana,p_William).
parent(p_Charles,p_William).
parent(p_Diana,p_Harry).
parent(p_Charles,p_Harry).

parent(c_m_Phillips,peter_Phillips).
parent(p_Anne,peter_Phillips).
parent(c_m_Phillips,z_Phillips).
parent(p_Anne,z_Phillips).

parent(s_Ferguson,p_Beatrice).
parent(p_Andrew,p_Beatrice).
parent(s_Ferguson,p_Eugenie).
parent(p_Andrew,p_Eugenie).

parent(s_r_Jones,j_v_Severn).
parent(p_Edward,j_v_Severn).
parent(s_r_Jones,l_l_m_Windsor).
parent(p_Edward,l_l_m_Windsor).

/****3rd Generation****/

parent(p_William,p_George).
parent(k_Middleton,p_George).
parent(p_William,p_Charlotte).
parent(k_Middleton,p_Charlotte).

parent(a_Kelly,s_Phillips).
parent(peter_Phillips,s_Phillips).
parent(a_Kelly,i_Phillips).
parent(peter_Phillips,i_Phillips).

parent(z_Phillips,m_g_Tindall).
parent(m_Tindall,m_g_Tindall).

/****Married****/

married(q_ElizabethII,p_Phillips).
married(p_Phillips,q_ElizabethII).

married(p_Charles,c_p_Bowles).
married(c_p_Bowles,p_Charles).

married(p_Anne,t_Laurence).
married(t_Laurence,p_Anne).

married(s_r_Jones,p_Edward).
married(p_Edward,s_r_Jones).

married(p_William,k_Middleton).
married(k_Middleton,p_William).

married(a_Kelly,peter_Phillips).
married(peter_Phillips,a_Kelly).

married(z_Phillips,m_Tindall).
married(m_Tindall,z_Phillips).

/****Divorced****/
divorced(p_Diana,p_Charles).
divorced(p_Charles,p_Diana).

divorced(cmPhillips,p_Anne).
divorced(p_Anne,c_m_Phillips).

divorced(s_Ferguson,p_Andrew).
divorced(p_Andrew,s_Ferguson).

/****Checking true or false****/

husband(Person,Wife):-married(Person,Wife),male(Person).
wife(Person,Husband):-married(Person,Husband),female(Person).
father(Parent,Child):-parent(Parent,Child),male(Parent).
mother(Parent,Child):-parent(Parent,Child),female(Parent).
child(Child,Parent):-parent(Parent,Child).
son(Child,Parent):-parent(Parent,Child),male(Child).
daughter(Child,Parent):-parent(Parent,Child),female(Child).

/****Checking Relationship****/

grandparent(GP,GC):-parent(X,GC),parent(GP,X).
grandmother(GM,GC):-mother(X,GC),mother(GM,X).
grandfather(GF,GC):-father(X,GC),father(GF,X).
grandchild(GC,GP):-grandparent(GP,GC).
grandson(GS,GP):-grandchild(GS,GP),male(GS).
granddaughter(GD,GP):-grandchild(GD,GP),female(GD).

sibling(Person1,Person2):-father(X,Person1),child(Person2,X).
brother(Person,Sibling):-sibling(Person,Sibling),male(Person).
sister(Person,Sibling):-sibling(Person,Sibling),female(Person).
aunt(Person,NieceNephew):-parent(X,NieceNephew),sibling(X,Person),female(Person).
uncle(Person,NieceNephew):-parent(X,NieceNephew),sibling(X,Person),male(Person).
niece(Person,AuntUncle):-(aunt(AuntUncle,Person);uncle(AuntUncle,Person)),female(Person).
nephew(Person,AuntUncle):-(aunt(AuntUncle,Person);uncle(AuntUncle,Person)),male(Person).