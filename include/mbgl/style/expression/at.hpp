#pragma once

#include <mbgl/style/expression/expression.hpp>
#include <mbgl/style/conversion.hpp>
#include <memory>

namespace mbgl {
namespace style {
namespace expression {

class At : public Expression {
public:
    At(std::unique_ptr<Expression> index_, std::unique_ptr<Expression> input_) :
        Expression(Kind::At, input_->getType().get<type::Array>().itemType),
        index(std::move(index_)),
        input(std::move(input_))
    {}
    
    static ParseResult parse(const mbgl::style::conversion::Convertible& value, ParsingContext& ctx);
    
    EvaluationResult evaluate(const EvaluationContext& params) const override;
    void eachChild(const std::function<void(const Expression&)>&) const override;

  static ParseResult parse(const mbgl::style::conversion::Convertible &value,
                           ParsingContext &ctx);

    std::vector<std::optional<Value>> possibleOutputs() const override {
        return { std::nullopt };
    }

    std::vector<std::optional<Value>> possibleOutputs() const override {
        return { std::nullopt };
    }
    
    std::string getOperator() const override { return "at"; }

private:
    std::unique_ptr<Expression> index;
    std::unique_ptr<Expression> input;
};

} // namespace expression
} // namespace style
} // namespace mbgl
