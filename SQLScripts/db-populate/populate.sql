BEGIN;

\i db-populate/user_.sql

\i db-populate/list_state.sql
\i db-populate/income_category.sql
\i db-populate/product_category.sql

\i db-populate/list.sql
\i db-populate/income.sql
\i db-populate/product.sql

COMMIT;
