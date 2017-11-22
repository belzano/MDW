package annotation.accessors.writer;


import annotation.EntityModelWriter;
import model.EntityModel;
import model.EntityModelContext;

public class AccessorWriter extends EntityModelWriter {

    public String writeEntityContentDefinition(EntityModel entityModel) {
        return "void Class::setBla(){}'";
    }

    public String writeEntityContentDeclaration(EntityModel entityModel) {
        return "void setBla();'";
    }

    public String writeContextDeclaration(EntityModelContext entityModelContext) {
        return "";
    }

    public String writeContextDefinition(EntityModelContext entityModelContext) {
        return "";
    }

}