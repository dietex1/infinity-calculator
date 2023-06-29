# Infinity Calculator

## Přehled

Tento projekt je textově orientovaná kalkulačka vyvinutá v C++. Hlavním účelem této aplikace je poskytnout funkcionalitu kalkulačky, podporu proměnných a import/export stavu kalkulačky. Aplikace umožňuje uživatelům provádět matematické operace včetně sčítání, odčítání, násobení, dělení, modulo operace a mocninné operace. Podporuje také operace faktorialu a zaokrouhlování, stejně jako přiřazení výrazů k proměnným pro pozdější použití. Uživatelé mohou interagovat s kalkulačkou prostřednictvím jednoduchého příkazového řádku.

## Popis

Aplikace je založena na modulárním designu, který izoluje různé funkcionality do samostatných tříd. Hlavní třídy projektu jsou:

- `Number`: Jedná se o abstraktní základní třídu reprezentující číselnou hodnotu. Tato třída má dvě odvozené třídy, `IntegerNumber` a `FloatNumber`, které poskytují specifickou implementaci pro celá a desetinná čísla.

- `Calculator`: Tato třída zahrnuje logiku kalkulačky. Udržuje mapu proměnných a jejich hodnot a poskytuje funkce pro parsování a vyhodnocování výrazů, provádění příkazů a import/export stavu kalkulačky.

- `UserInterface`: Tato třída poskytuje interaktivní příkazový řádek pro uživatele pro zadávání příkazů a výrazů a zobrazuje výsledky nebo chybové zprávy.

## Aplikace polymorfismu

Polymorfismus je v tomto projektu intenzivně využíván prostřednictvím abstraktní základní třídy `Number` a jejích dvou odvozených tříd, `IntegerNumber` a `FloatNumber`. Třída `Number` deklaruje sadu čistě virtuálních funkcí pro provádění matematických operací a tyto funkce jsou v `IntegerNumber` a `FloatNumber` implementovány odlišně v závislosti na specifických požadavcích celočíselné a desetinné aritmetiky. Tato aplikace polymorfismu nám umožňuje psát kód, který pracuje s ukazateli nebo referencemi `Number`, a správná funkce bude volána na základě skute

čného typu objektu.

Například ve funkci `Calculator::calculateRPN()` máme zásobník objektů `shared_ptr<Number>` a používáme operátory `+`, `-`, `*`, `/`, `%`, `^`, `~`, `!` k provedení výpočtů. Správná verze funkce operátoru (celočíselná nebo desetinná) bude volána v závislosti na tom, zda ukazatele ukazují na objekty `IntegerNumber` nebo `FloatNumber`.

## Návrh architektury

Architektura projektu je navržena s důrazem na modularitu a rozdělení záležitostí. Hierarchie tříd `Number` zahrnuje reprezentaci a operace čísel. Třída `Calculator` zahrnuje logiku parsování a vyhodnocování výrazů a řízení stavu proměnných. Třída `UserInterface` zahrnuje interakci s uživatelem, přijímání uživatelských vstupů a zobrazování výstupů nebo chybových zpráv.

Tento návrh činí kód snadněji srozumitelným, testovatelným a udržitelným. Každá třída má jasnou odpovědnost a interaguje s ostatními prostřednictvím dobře definovaných rozhraní. Použití polymorfismu prostřednictvím hierarchie tříd `Number` činí kód flexibilní a rozšiřitelný. Například, pokud chceme v budoucnu podporovat nový číselný typ, můžeme jednoduše vytvořit novou odvozenou třídu `Number`.

## Parsing, reverzní polská notace (RPN) a ošetření výjimek

### Parsing

Parsování uživatelského vstupu je řešeno v třídě `Calculator`. Tato třída bere jako vstup řetězec matematického výrazu a vrátí sekvenci tokenů. Tokenizace zahrnuje rozdělení vstupního řetězce podle mezer a poté určení typu každého tokenu - může to být číslo, název proměnné nebo operátor. Pro čísla a názvy proměnných parser také kontroluje, zda je formát platný, tedy číslo by mělo obsahovat pouze číslice a maximálně jednu desetinnou tečku, název proměnné by měl začínat písmenem a obsahovat pouze písmena a číslice. Funkce `shuntingYard()` také kontroluje závorky pro správné ř

ízení pořadí operací. Používá algoritmus Shunting Yard pro převod výrazu z infixe na reverzní polskou notaci (RPN), která je snadněji vyhodnocovatelná.

### Ošetření výjimek

Projekt používá robustní ošetření výjimek, aby zajistil stabilitu a přívětivost aplikace pro uživatele. Každá třída je navržena s obranným programovacím přístupem, což znamená, že kontroluje potenciální chyby a vyvolává výjimky, když se něco pokazí.

Například během parsování, pokud vstupní řetězec obsahuje neplatné znaky nebo závorky nejsou správně spárované, funkce vyvolá výjimku s chybovou zprávou. Třída `UserInterface` má hlavní smyčku, kde volá funkce třídy `Calculator` uvnitř try bloku. Pokud je vyvolána výjimka, je zachycena v bloku catch, a chybová zpráva je zobrazena uživateli. Tímto způsobem, i když dojde k chybě, program nespadne a uživatel může pokračovat v používání kalkulačky.


