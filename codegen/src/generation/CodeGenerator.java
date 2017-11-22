package generation;

import model.EntityModel;
import model.EntityModelContext;

interface CodeGenerator {

    String EOL = "\n";
    String TAB = "\t";
    String QUOTE = "\"";

    void writeEntityCode(EntityModel entityModel);

    void writeContextCode(EntityModelContext entityModelContext);

}
