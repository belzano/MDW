package annotation;

import model.EntityTypeModel;
import model.EntityModelContext;

public interface FieldDecorator {

    void updateModel(EntityTypeModel model, EntityModelContext context);

}

