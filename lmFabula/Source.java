import java.io.FileInputStream;
import java.io.IOException;

import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

public class Source
{

    public static void main(String[] args) throws IOException 
    {
        System.out.println("Compiling Fabula file...");
        ANTLRInputStream input = new ANTLRInputStream(new FileInputStream("fabula-example.fab")); 
        FabulaLexer lexer = new FabulaLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        FabulaParser parser = new FabulaParser(tokens);
        ParseTree tree = parser.prog(); // see the grammar ->
                                                    // starting point for
                                                    // parsing a java file


        CustomVisitor<?> visitor = new CustomVisitor<>(); // extends JavaBaseVisitor<Void>
                                                // and overrides the methods
                                                // you're interested
        
        
        visitor.visit(tree);
        
        if(visitor.error!=null)
        	System.out.println(visitor.error);

        System.out.println("Done");
    }
}