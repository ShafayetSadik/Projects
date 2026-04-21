clc
morse=struct;
morse.a='.-';
morse.b='-...';
morse.c='-.-.';
morse.d='-..';
morse.e='.';
morse.f='..-.';
morse.g='--.';
morse.h='....';
morse.i='..';
morse.j='.---';
morse.k='-.-';
morse.l='.-..';
morse.m='--';
morse.n='-.';
morse.o='---';
morse.p='.--.';
morse.q='--.-';
morse.r='.-.';
morse.s='...';
morse.t='-';
morse.u='..-';
morse.v='...-';
morse.w='.--';
morse.x='-..-';
morse.y='-.--';
morse.z='--..';
morse.n1='.----';
morse.n2='..---';
morse.n3='...--';
morse.n4='....-';
morse.n5='.....';
morse.n5='.....';
morse.n6='-....';
morse.n7='--...';
morse.n8='---..';
morse.n9='----.';
morse.n0='-----';
morse.sc='.-.''';
morse.scv={['.-.-.-'],['-.-.-.'],['--..--'],['-.-.-.-']};


a=input('press e for Morse encoding and d for morse deconing: ','s')

switch a
    case 'e'
text=input('enter text: ','s')
%fprintf('input: %s\n', text)
text=lower(text);
l=length(text);
m=[];

for i = 1:l
    if text(i)== ' '
        m=[m '/'];
    elseif isvarname(text(i))
        m= [m getfield(morse,text(i))];
        m= [m ' '];
    elseif ~isempty(str2num(text(i)))
        m= [m getfield(morse,['n',text(i)])];
        m= [m ' '];
    elseif findstr(text(i),morse.sc)
        m= [m char(morse.scv(findstr(text(i),morse.sc)))];
          m= [m ' '];
    end
end
    fprintf('Output: %s\n', m);
    t=1:6000;
dot=sin(t(1:600));
dash=sin(t(1:2000));
ssp= zeros(1,2000);
lsp= zeros(1,4000);

ms=[];

for i= 1:length(m)
    if strcmp(m(i),'.')
        ms=[ms dot ssp];
    elseif strcmp(m(i),'-')
        ms=[ms dash ssp];
    elseif strcmp(m(i),' ')
        ms=[ms lsp];
    elseif strcmp(m(i),'/')
        ms=[ms lsp ssp];
    end
end

p=audioplayer(ms,13000);
play(p)
% Save Morse code sound to a .wav file
filename = 'sound4.wav';
audiowrite(filename, ms, 13000);
disp(['Morse code saved as ', filename]);

    case 'd'
    %decode
    code=input('Enter Morse: ','s')
    t=1:6000;
dot=sin(t(1:600));
dash=sin(t(1:2000));
ssp= zeros(1,2000);
lsp= zeros(1,4000);

ms=[];

for i= 1:length(code)
    if strcmp(code(i),'.')
        ms=[ms dot ssp];
    elseif strcmp(code(i),'-')
        ms=[ms dash ssp];
    elseif strcmp(code(i),' ')
        ms=[ms lsp];
    elseif strcmp(code(i),'/')
        ms=[ms lsp ssp];
    end
end

p=audioplayer(ms,13000);
play(p)
    dec=[];
    code=[code ' '];
    lcode=[];
    
    for j= 1:length(code)
        if (strcmp(code(j),' ')|strcmp(code(j),'/'))
            for i= double('a'):double('z')
                let=getfield(morse,char(i));
                if strcmp(lcode,let)
                    dec=[dec char(i)];
                end
            end
            for i=0:9
                num=getfield(morse,['n',num2str(i)]);
                if strcmp(lcode,num)
                    dec=[dec num2str(i)];
                end
            end
            for i=1:4
                scv=char(morse.scv(i));
                if strcmp(lcode,scv)
                    dec=[dec ,morse.sc(i)];
                end
            end
            lcode=[];
        else
            lcode=[lcode code(j)];
        end
        if strcmp(code(j),'/')
            dec=[dec ' '];
        end
    end
    fprintf('Decoded Output: %s\n', dec);
    

end  

%sound
