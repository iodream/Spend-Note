BEGIN;

\i db-populate/user_.sql

\i db-populate/list_state.sql
\i db-populate/income_category.sql
\i db-populate/product_category.sql

\i db-populate/list.sql
\i db-populate/income.sql
\i db-populate/product.sql

\i db-populate/period_type.sql
\i db-populate/periodic_product.sql
\i db-populate/periodic_income.sql

COMMIT;
